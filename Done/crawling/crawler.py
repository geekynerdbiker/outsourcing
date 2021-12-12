import requests
import matplotlib.pyplot as plt
from konlpy.tag import Kkma
from bs4 import BeautifulSoup
from collections import Counter
import re
import json


def fix_korean():
    import platform

    if platform.system() == 'Darwin':
        plt.rc('font', family='AppleGothic')
    elif platform.system() == 'Windows':
        plt.rc('font', family='Malgun Gothic')
    elif platform.system() == 'Linux':  # if use colab
        # !wget "https://www.wfonts.com/download/data/2016/06/13/malgun-gothic/malgun.ttf"
        # !mv malgun.ttf /usr/share/fonts/truetype/
        # import matplotlib.font_manager as fm
        # fm._rebuild()
        plt.rc('font', family='Malgun Gothic')
    plt.rcParams['axes.unicode_minus'] = False


def get_titles():
    news_dict = []

    query = '삼성'
    news_num = 10
    query = query.replace(' ', '+')

    news_url = 'https://search.naver.com/search.naver?where=news&sm=tab_jum&query={}'

    req = requests.get(news_url.format(query))
    soup = BeautifulSoup(req.text, 'html.parser')

    idx = 0
    cur_page = 1

    print('제목 크롤링 중...')

    while idx < news_num:

        table = soup.find('ul', {'class': 'list_news'})
        li_list = table.find_all('li', {'id': re.compile('sp_nws.*')})
        area_list = [li.find('div', {'class': 'news_area'}) for li in li_list]
        a_list = [area.find('a', {'class': 'news_tit'}) for area in area_list]

        for n in a_list[:min(len(a_list), news_num - idx)]:
            news_dict.append(n.get('title'))
            idx += 1

        cur_page += 1

        pages = soup.find('div', {'class': 'sc_page_inner'})
        url = [p for p in pages.find_all('a') if p.text == str(cur_page)][0].get('href')

        req = requests.get('https://search.naver.com/search.naver' + url)
        soup = BeautifulSoup(req.text, 'html.parser')

    return news_dict


def get_comments():
    comments_dict = []
    urls = ["https://news.naver.com/main/read.naver?mode=LSD&mid=shm&sid1=105&oid=015&aid=0004638999",
            "https://news.naver.com/main/read.naver?mode=LSD&mid=shm&sid1=105&oid=016&aid=0001923515",
            "https://news.naver.com/main/read.naver?mode=LSD&mid=shm&sid1=105&oid=015&aid=0004639419",
            "https://news.naver.com/main/read.naver?mode=LSD&mid=shm&sid1=101&oid=018&aid=0005104521", ]

    print('댓글 크롤링 중...')

    for url in urls:
        co_list = []

        oid = url.split("oid=")[1].split("&")[0]  # 422
        aid = url.split("aid=")[1]  # 0000430957
        page = 1
        header = {
            "User-agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.181 Safari/537.36",
            "referer": url,
        }

        while True:
            c_url = "https://apis.naver.com/commentBox/cbox/web_neo_list_jsonp.json?ticket=news&templateId=default_society&pool=cbox5&_callback=jQuery1707138182064460843_1523512042464&lang=ko&country=&objectId=news" + oid + "%2C" + aid + "&categoryId=&pageSize=20&indexSize=10&groupId=&listType=OBJECT&pageType=more&page=" + str(
                page) + "&refresh=false&sort=FAVORITE"
            r = requests.get(c_url, headers=header)
            cont = BeautifulSoup(r.content, "html.parser")
            total_comm = str(cont).split('comment":')[1].split(",")[0]

            match = re.findall('"contents":([^\*]*),"userIdNo"', str(cont))
            co_list.append(match)
            if int(total_comm) <= ((page) * 20):
                break
            else:
                page += 1

        def flatten(l):
            flat_list = []
            for elem in l:
                if type(elem) == list:
                    for e in elem:
                        flat_list.append(e)
                else:
                    flat_list.append(elem)
            return flat_list

        allCommetns = flatten(co_list)

        for comment in allCommetns:
            comments_dict.append(comment)

    return comments_dict


def get_words(title, comment):
    words = []

    for word in title:
        splits = word.split(' ')
        for w in splits:
            words.append(w)

    for line in comment:
        for word in line:
            splits = word.split(' ')
            for w in splits:
                words.append(w)
    return words


class Miner():

    def data_list(wordname):
        with open('data/SentiWord_info.json', encoding='utf-8-sig', mode='r') as f:
            data = json.load(f)
        result = ['None', 'None']
        for i in range(0, len(data)):
            if data[i]['word'] == wordname:
                result.pop()
                result.pop()
                result.append(data[i]['word_root'])
                result.append(data[i]['polarity'])

        r_word = result[0]
        s_word = result[1]

        return r_word, s_word


if __name__ == '__main__':
    words = get_words(get_titles(), get_comments())
    print(words)
    m = Miner
    score = 0

    rst = []
    for w in words:
        data = m.data_list(w)
        if data[1] != 'None':
            rst.append(data)

    word_count = {}  # 빈 set

    for s in rst:
        word_count[s[0]] = word_count.get(s[0], 0) + 1
        score += int(s[1])

    c = Counter(word_count)
    t10 = c.most_common(10)

    ratio = []
    labels = []

    for i in t10:
        labels.append(i[0])
        ratio.append(i[1])

    fix_korean()
    plt.pie(ratio, labels=labels, autopct='%.1f%%')
    plt.title("기업: 삼성")
    plt.show()

    print("score is" + str(score))
