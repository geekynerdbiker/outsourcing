import re
import json
import requests
from bs4 import BeautifulSoup
from collections import Counter
import matplotlib.pyplot as plt


class Miner:
    def data_list(wordname):
        with open('data.json', encoding='utf-8-sig', mode='r') as f:
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


def get_titles(keyword):
    news_dict = []

    query = keyword
    news_num = 200
    query = query.replace(' ', '+')

    news_url = 'https://search.naver.com/search.naver?where=news&sm=tab_jum&query={}'

    req = requests.get(news_url.format(query))
    soup = BeautifulSoup(req.text, 'html.parser')

    idx = 0
    cur_page = 1

    print('\"' + keyword + '\" 관련 기사 크롤링 중...')

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


def get_words(title):
    words = []

    for word in title:
        splits = word.split(' ')
        for w in splits:
            words.append(w)

    return words


def get_score(keyword):
    words = get_words(get_titles(keyword))
    m = Miner
    pos = 0
    neg = 0

    rst = []
    for w in words:
        data = m.data_list(w)
        if data[1] != 'None':
            rst.append(data)

    word_count = {}

    for s in rst:
        word_count[s[0]] = word_count.get(s[0], 0) + 1
        if int(s[1]) > 0:
            pos += 1
        elif int(s[1]) < 0:
            neg += 1

    c = Counter(word_count)
    t5 = c.most_common(5)

    ratio = []
    labels = []

    for i in t5:
        labels.append(i[0])
        ratio.append(i[1])

    return pos, neg, labels, ratio


if __name__ == '__main__':
    table = [get_score('삼성 마케팅'), get_score('삼성 재무'), get_score('삼성 생산'), get_score('삼성 인적'), get_score('삼성 기술'),get_score('삼성 경영')]

    labels = ['삼성 마케팅', '삼성 재무', '삼성 생산', '삼성 인적', '삼성 기술', '삼성 경영']
    pos_ratio = []
    neg_ratio = []

    for i in range(len(table)):
        if table[i][1] == 0:
            if table[i][0] == 0:
                pos_ratio.append(0)
                neg_ratio.append(0)
        else:
            pos = table[i][0] / (table[i][0] + table[i][1]) * 100
            neg = table[i][1] / (table[i][0] + table[i][1]) * 100
            pos_ratio.append(pos)
            neg_ratio.append(neg)

    for i in range(len(table)):
        plt.rc('font', family='NanumBarunGothic')
        plt.pie(table[i][3], labels=table[i][2], autopct='%.1f%%')
        plt.title(labels[i])
        plt.show()

    x1 = [1, 3, 5, 7, 9, 11]
    x2 = [1.3, 3.3, 5.3, 7.3, 9.3, 11.3]

    plt.rc('font', family='NanumBarunGothic')
    plt.bar(x1, pos_ratio, color='b', width=0.3, label='긍정도')
    plt.legend()

    plt.rc('font', family='NanumBarunGothic')
    plt.bar(x2, neg_ratio, color='r', width=0.3, label='부정도')
    plt.legend()

    plt.xticks(x1, labels)
    plt.title("기업: 삼성")
    plt.show()
