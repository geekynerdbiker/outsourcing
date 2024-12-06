import datetime
import json
import math
import random
import re
import threading
import urllib.parse
from urllib import request

from apiclient.discovery import build
from bs4 import BeautifulSoup
from django.conf import settings
from django.core.paginator import Paginator
from django.db.models import Q
from django.http import JsonResponse
from django.shortcuts import render
from django.views.decorators.csrf import csrf_exempt

from .models import (Lazylet_Set, Lazylet_Term, Log, User, WordChain_Match,
                         WordChain_Player, WordChain_Word)

version = "2.3"


def lazylet_create_soup_with_url(url):
    handler = request.urlopen(url)
    source = handler.read().decode('utf-8')
    return BeautifulSoup(source, 'html.parser')


def lazylet_create_soup_with_query(query):
    url = 'http://dic.daum.net/search.do?dic=eng&q=' + \
        urllib.parse.quote(query)
    return lazylet_create_soup_with_url(url)


def lazylet_create_soup_with_wordid(wordid):
    url = 'http://dic.daum.net/word/view.do?wordid=' + wordid
    return lazylet_create_soup_with_url(url)


def lazylet_get_wordid(url):
    return re.findall('ekw[\d]+', url)[0]


def lazylet_get_meaning_words(query):
    soup = lazylet_create_soup_with_query(query)
    refresh_meta = soup.find('meta', attrs={'http-equiv': 'Refresh'})
    if refresh_meta is not None:
        wordid = lazylet_get_wordid(refresh_meta.get('content'))
        soup = lazylet_create_soup_with_wordid(wordid)
    final_page_anchor = soup.find(
        'a', class_='txt_cleansch')  # first link_word
    if final_page_anchor is not None:
        wordid = lazylet_get_wordid(final_page_anchor.get('href'))
        soup = lazylet_create_soup_with_wordid(wordid)
    meaning_div = soup.find('ul', class_='list_mean')
    meaning_words = re.split('\d{1,2}\.', meaning_div.get_text())
    if meaning_words[0] == '\n':
        meaning_words = meaning_words[1:]
    meaning_words = [w.strip() for w in meaning_words]
    meaning_words = [w for w in meaning_words if w != '']

    return meaning_words


class Lazylet_GetMeaningWordsThread(threading.Thread):
    def __init__(self, set_, *args, **kwargs):
        self.set = set_
        super(Lazylet_GetMeaningWordsThread, self).__init__(*args, **kwargs)

    def run(self):
        term_set = Lazylet_Term.objects.filter(lazylet_set=self.set)
        for term in term_set:
            meaning_words = lazylet_get_meaning_words(term.term)
            if meaning_words is None:
                continue
            term.definition = ", ".join(meaning_words)

            service = build("customsearch", "v1",
                            developerKey=settings.GOOGLE_DEVELOPER_KEY)

            res = service.cse().list(
                q=term.term,
                cx=settings.GOOGLE_CX,
                searchType='image',
                num=1,
                imgType='clipart',
                fileType='png',
                safe='off'
            ).execute()

            if 'items' in res:
                term.image_url = res['items'][0]['link']

            term.save(update_fields=['definition', 'image_url'])


def keyboard(request):
    if True:
        return JsonResponse({'error': 'Bad Request'}, status=400)

    return JsonResponse({
        'type': 'text'
    })


@csrf_exempt
def answer(request):

    json_str = ((request.body).decode('utf-8'))
    received_json_data = json.loads(json_str)
    datacontent = received_json_data['userRequest']['utterance']
    user_key = received_json_data['userRequest']['user']['properties']['plusfriendUserKey']

    user = User.get_or_create(user_key)

    bot_user = User.get_or_create('shallbox')
    if not bot_user.user_name:
        bot_user.set_name("쉘박스")

    start = datetime.datetime.now()

    cmd = datacontent.split()[0]
    data = re.sub(cmd + " ", "", datacontent)

    if user.state == 'lazylet' and cmd == '/주문조회':
        try:
            set_ = Lazylet_Set.objects.get(user=user)
        except Lazylet_Set.DoesNotExist:
            set_ = Lazylet_Set(user=user, title=str(user.user_name) + "의 세트")
            set_.save()

        if not Lazylet_Term.objects.filter(lazylet_set=set_).exists():
            setempty = "[주문조회]\n 주문내역이 없습니다."

            response_body = {
                'version': "2.0",
                'template': {
                    'outputs': [
                        {
                            'simpleText': {
                                'text': setempty
                            }
                        }
                    ],
                    'quickReplies': [
                        {
                            'label': '/내카드',
                            'action': 'message',
                            'messageText': '/내카드'
                        },
                        {
                            'label': '/카드추가',
                            'action': 'message',
                            'messageText': '/카드추가'
                        }
                    ]
                }

            }
        else:
            term_list = Lazylet_Term.objects.filter(lazylet_set=set_)
            paginator = Paginator(term_list, 5)  # Show 5 terms per page

            page = data
            terms = paginator.get_page(page)
            items = []
            for t in terms:
                item = {
                    'title': t.term,
                    'description': t.definition,
                    'link': {
                        'web': 'http://dic.daum.net/search.do?dic=eng&q=' + t.term
                    }
                }
                if t.image_url:
                    item['imageUrl'] = t.image_url
                items.append(item)
            quickReplies = [
                {
                    'label': '내보내기',
                    'action': 'message',
                    'messageText': '/내보내기'
                },
                {
                    'label': '/내카드',
                    'action': 'message',
                    'messageText': '/내카드'
                },
                {
                    'label': '/카드추가',
                    'action': 'message',
                    'messageText': '/카드추가'
                },
                {
                    'label': '/지우기',
                    'action': 'message',
                    'messageText': '/지우기'
                }
            ]
            if terms.has_next():
                quickReplies.insert(0, {
                    'label': '다음',
                    'action': 'message',
                    'messageText': '/내카드 ' + str(terms.next_page_number())
                })
            if terms.has_previous():
                quickReplies.insert(0, {
                    'label': '이전',
                    'action': 'message',
                    'messageText': '/내카드 ' + str(terms.previous_page_number())
                })
            response_body = {
                'version': "2.0",
                'template': {
                    'outputs': [
                        {
                            'listCard': {
                                'header': {
                                    'title': '내 카드'
                                },
                                'items': items
                            }
                        }
                    ],
                    'quickReplies': quickReplies
                }

            }

    elif user.state == 'lazylet' and cmd == '/주문변경':
        try:
            set_ = Lazylet_Set.objects.get(user=user)
        except Lazylet_Set.DoesNotExist:
            set_ = Lazylet_Set(user=user, title=str(user.user_name) + "의 세트")
            set_.save()

        if not Lazylet_Term.objects.filter(lazylet_set=set_).exists():
            setempty = "[귀찮렛 베타]\n세트가 비어 있습니다."

            response_body = {
                'version': "2.0",
                'template': {
                    'outputs': [
                        {
                            'simpleText': {
                                'text': setempty
                            }
                        }
                    ],
                    'quickReplies': [
                        {
                            'label': '/내카드',
                            'action': 'message',
                            'messageText': '/내카드'
                        },
                        {
                            'label': '/카드추가',
                            'action': 'message',
                            'messageText': '/카드추가'
                        }
                    ]
                }

            }
        else:
            term_set = Lazylet_Term.objects.filter(lazylet_set=set_)
            response_body = {
                'version': "2.0",
                'template': {
                    'outputs': [
                        {
                            'simpleText': {
                                'text': "\n".join(['%s\t%s' % (term.term, term.definition) for term in term_set])
                            }
                        },
                        {
                            'basicCard': {
                                'description': 'Quizlet을 사용하고 있나요? 단어 목록을 복사하여 Quizlet에 붙여넣기만 하면 됩니다. 간단하죠?',
                                'buttons': [
                                    {
                                        'action': 'webLink',
                                        'label': 'Quizlet으로 가져오기',
                                        'webLinkUrl': 'https://quizlet.com/ko/help/2444107/import-content-to-quizlet'
                                    }
                                ]
                            }
                        }
                    ],
                    'quickReplies': [
                        {
                            'label': '/내카드',
                            'action': 'message',
                            'messageText': '/내카드'
                        },
                        {
                            'label': '/카드추가',
                            'action': 'message',
                            'messageText': '/카드추가'
                        },
                        {
                            'label': '/지우기',
                            'action': 'message',
                            'messageText': '/지우기'
                        }
                    ]
                }

            }

    elif user.state == 'lazylet' and cmd == '/메뉴보기':
        try:
            set_ = Lazylet_Set.objects.get(user=user)
        except Lazylet_Set.DoesNotExist:
            set_ = Lazylet_Set(user=user, title=str(user.user_name) + "의 세트")
            set_.save()

        if not Lazylet_Term.objects.filter(lazylet_set=set_).exists():
            setempty = "[귀찮렛 베타]\n여러분이 배우고 있는 단어나 문장을 입력하세요. Daum 사전 덕분에 뜻이 그 옆에 마법처럼 나타납니다."

            response_body = {
                'version': "2.0",
                'template': {
                    'outputs': [
                        {
                            'simpleText': {
                                'text': setempty
                            }
                        }
                    ],
                    'quickReplies': [
                        {
                            'label': '/내카드',
                            'action': 'message',
                            'messageText': '/내카드'
                        }
                    ]
                }

            }
        else:
            term_set = Lazylet_Term.objects.filter(lazylet_set=set_)
            response_body = {
                'version': "2.0",
                'template': {
                    'outputs': [
                        {
                            'simpleText': {
                                'text': "\n".join(['%s\t%s' % (term.term, term.definition) for term in term_set])
                            }
                        }
                    ],
                    'quickReplies': [
                        {
                            'label': '/내카드',
                            'action': 'message',
                            'messageText': '/내카드'
                        },
                        {
                            'label': '/지우기',
                            'action': 'message',
                            'messageText': '/지우기'
                        }
                    ]
                }

            }

    elif user.state == 'lazylet' and cmd == '/주문취소':
        try:
            set_ = Lazylet_Set.objects.get(user=user)
        except Lazylet_Set.DoesNotExist:
            set_ = Lazylet_Set(user=user, title=str(user.user_name) + "의 세트")
            set_.save()
        Lazylet_Term.objects.filter(lazylet_set=set_).delete()
        setempty = "[귀찮렛 베타]\n세트가 비어 있습니다."
        response_body = {
            'version': "2.0",
            'template': {
                'outputs': [
                    {
                        'simpleText': {
                            'text': setempty
                        }
                    }
                ],
                'quickReplies': [
                    {
                        'label': '/내카드',
                        'action': 'message',
                        'messageText': '/내카드'
                    },
                    {
                        'label': '/카드추가',
                        'action': 'message',
                        'messageText': '/카드추가'
                    }
                ]
            }
        }

    elif user.state == 'lazylet' and not cmd.startswith('/'):
        words = re.findall("[\w']+", datacontent)
        try:
            set_ = Lazylet_Set.objects.get(user=user)
        except Lazylet_Set.DoesNotExist:
            set_ = Lazylet_Set(user=user, title=str(user.user_name) + "의 세트")
            set_.save()
        for w in words:
            term = Lazylet_Term(lazylet_set=set_, term=w,
                                definition="로드 중...", image_url="")
            term.save()
        t = Lazylet_GetMeaningWordsThread(set_)
        t.start()
        t.join(3)

        if len(words) == 1:
            basicCard = {
                'description': '[귀찮렛 베타]\n성공적으로 추가되었습니다.\n모든 카드를 보려면 /내카드 를 입력하십시오.\n\n %s\t%s' % (words[0], Lazylet_Term.objects.get(lazylet_set=set_, term=words[0]).definition),
                'buttons': [
                    {
                        'action': 'webLink',
                        'label': 'Daum 사전에서 보기',
                        'webLinkUrl': 'http://dic.daum.net/search.do?dic=eng&q=' + words[0]
                    }
                ]
            }
            if Lazylet_Term.objects.get(lazylet_set=set_, term=words[0]).image_url:
                basicCard['thumbnail'] = {
                    'imageUrl': Lazylet_Term.objects.get(lazylet_set=set_, term=words[0]).image_url
                }
            response_body = {
                'version': "2.0",
                'template': {
                    'outputs': [
                        {
                            'basicCard': basicCard
                        }
                    ],
                    'quickReplies': [
                        {
                            'label': '/내카드',
                            'action': 'message',
                            'messageText': '/내카드'
                        },
                        {
                            'label': '/지우기',
                            'action': 'message',
                            'messageText': '/지우기'
                        }
                    ]
                }

            }
        else:
            response_body = {
                'version': "2.0",
                'template': {
                    'outputs': [
                        {
                            'simpleText': {
                                'text': '[귀찮렛 베타]\n성공적으로 추가되었습니다.\n모든 카드를 보려면 /내카드 를 입력하십시오.\n\n ' + "\n".join(['%s\t%s' % (w, Lazylet_Term.objects.get(lazylet_set=set_, term=w).definition) for w in words])
                            }
                        }
                    ],
                    'quickReplies': [
                        {
                            'label': '/내카드',
                            'action': 'message',
                            'messageText': '/내카드'
                        },
                        {
                            'label': '/지우기',
                            'action': 'message',
                            'messageText': '/지우기'
                        }
                    ]
                }

            }

    elif user.state == 'setusername' and not cmd.startswith('/'):
        if not User.objects.filter(user_name=datacontent).exists():
            user.set_name(datacontent)

            user.state = 'home'
            user.save(update_fields=['state'])

            setusername = "안녕하세요 " + user.user_name + "님! 선우봇에 오신 것을 환영합니다!"

            response_body = {
                'version': "2.0",
                'template': {
                    'outputs': [
                        {
                            'simpleText': {
                                'text': setusername
                            }
                        }
                    ],
                    'quickReplies': [
                        {
                            'label': '/끝말톡',
                            'action': 'message',
                            'messageText': '/끝말톡'
                        },
                        {
                            'label': '/귀찮렛',
                            'action': 'message',
                            'messageText': '/귀찮렛'
                        },
                        {
                            'label': '/도움말',
                            'action': 'message',
                            'messageText': '/도움말'
                        }
                    ]
                }

            }
        else:
            setusername = "사용자 이름이 이미 존재합니다.\n다른 사용자 이름을 입력하세요."

            response_body = {
                'version': "2.0",
                'template': {
                    'outputs': [
                        {
                            'simpleText': {
                                'text': setusername
                            }
                        }
                    ]
                }

            }

    elif cmd == '/귀찮렛':
        user.state = 'lazylet'
        user.save(update_fields=['state'])

        lazylet = "[귀찮렛 베타]\n어학 사전을 찾는 것이 귀찮으신가요? 선우봇 귀찮렛 베타가 대신 찾아드립니다."

        response_body = {
            'version': "2.0",
            'template': {
                'outputs': [
                    {
                        'basicCard': {
                            'description': lazylet,
                            'thumbnail': {
                                'imageUrl': 'https://ryuhyuncom.files.wordpress.com/2019/01/lazylet-1.png'
                            }
                        }
                    }
                ],
                'quickReplies': [
                    {
                        'label': '/내카드',
                        'action': 'message',
                        'messageText': '/내카드'
                    },
                    {
                        'label': '/카드추가',
                        'action': 'message',
                        'messageText': '/카드추가'
                    },
                    {
                        'label': '/지우기',
                        'action': 'message',
                        'messageText': '/지우기'
                    }
                ]
            }

        }

    elif cmd == '/끝말톡':
        user.state = 'wordchain'
        user.save(update_fields=['state'])

        wordchain = "[끝말톡 이전 안내]\n\n끝말톡 온라인의 정식 버전이 출시되었어요!\n새로운 플러스친구 @끝말톡 (http://pf.kakao.com/_YzzWj)에서 지금 만나실 수 있습니다.\n오픈 베타 서비스가 종료됨에 따라, 모든 기존 사용자 데이터는 초기화되는 점에 유의하시기 바랍니다.\n\n그동안 끝말톡 오픈 베타를 이용해주셔서 감사드리며 더 좋은 서비스로 찾아뵙도록 하겠습니다."

        response_body = {
            'version': "2.0",
            'template': {
                'outputs': [
                    {
                        'basicCard': {
                            'description': wordchain,
                            'thumbnail': {
                                'imageUrl': 'http://ryuhyun.com/wp-content/uploads/2019/02/wordchain-1.png',
                                'fixedRatio': True
                            }
                        }
                    }
                ],
                'quickReplies': [
                    {
                        'label': '/랭킹',
                        'action': 'message',
                        'messageText': '/랭킹'
                    }
                ]
            }

        }

    else:
        user.state = 'home'
        user.save(update_fields=['state'])

        help = "봇 이름 : 선우봇\n버전 : " + version + \
            "\n제작자 : 류현(박선우)\n\n 앱을 실행하려면 /<앱 이름>을 사용하십시오."

        response_body = {
            'version': "2.0",
            'template': {
                'outputs': [
                    {
                        'simpleText': {
                            'text': help
                        }
                    }
                ],
                'quickReplies': [
                    {
                        'label': '/끝말톡',
                        'action': 'message',
                        'messageText': '/끝말톡'
                    },
                    {
                        'label': '/귀찮렛',
                        'action': 'message',
                        'messageText': '/귀찮렛'
                    },
                    {
                        'label': '/도움말',
                        'action': 'message',
                        'messageText': '/도움말'
                    }
                ]
            }

        }

    time_diff = datetime.datetime.now() - start

    if not user.user_name:
        user.state = 'setusername'
        user.save(update_fields=['state'])

        setusername = "사용자 이름이 설정되지 않았습니다.\n선우봇에서 사용할 사용자 이름을 입력하세요."

        response_body = {
            'version': "2.0",
            'template': {
                'outputs': [
                    {
                        'simpleText': {
                            'text': setusername
                        }
                    }
                ]
            }

        }

    Log.write(user, datacontent, str(response_body), time_diff.total_seconds())

    return JsonResponse(response_body)
