import json
import time
import requests
import hashlib
import hmac
import base64


# 네이버 광고 API에서 제공하는 공식 예제 클래스 및 함수
class Signature:
    @staticmethod
    def generate(timestamp, method, uri, secret_key):
        message = "{}.{}.{}".format(timestamp, method, uri)
        hash = hmac.new(bytes(secret_key, "utf-8"), bytes(message, "utf-8"), hashlib.sha256)

        hash.hexdigest()
        return base64.b64encode(hash.digest())


def get_header(method, uri, api_key, secret_key, customer_id):
    timestamp = str(round(time.time() * 1000))
    signature = Signature.generate(timestamp, method, uri, SECRET_KEY)
    return {'Content-Type': 'application/json; charset=UTF-8', 'X-Timestamp': timestamp, 'X-API-KEY': API_KEY,
            'X-Customer': str(CUSTOMER_ID), 'X-Signature': signature}


# 검색광고 API 정보
BASE_URL = 'https://api.searchad.naver.com'
API_KEY = '0100000000be4fc6fe387be61d263be45e97a7c2a5a983aab88bfd4e147389953fbae5ad10'
SECRET_KEY = 'AQAAAAC+T8b+OHvmHSY75F6Xp8Kl7B/3XROyknGvows52PU3nw=='
CUSTOMER_ID = '1885595'

uri = '/keywordstool'
method = 'GET'

query = {
    'siteId': '',
    'biztpID': '',
    'hintKeywords': input('keyword: '),
    'event': '',
    'month': '',
    'showDetail': '1'
}

r = requests.get(BASE_URL + uri, params=query,
                 headers=get_header(method, uri, API_KEY, SECRET_KEY, CUSTOMER_ID))
l = list()

if r.status_code == 200:
    try:
        r_data = r.json()
        print(r_data)
        # 모바일, PC의 결과가 따로 나오므로 합산하여 계산
        for i in range(len(r_data['keywordList'])):
            click = r_data['keywordList'][i]['monthlyAvePcClkCnt'] + r_data['keywordList'][i][
                'monthlyAveMobileClkCnt']
            search = r_data['keywordList'][i]['monthlyPcQcCnt'] + r_data['keywordList'][i]['monthlyMobileQcCnt']

            d = dict()
            d['name'] = r_data['keywordList'][i]['relKeyword']
            d['artworks'] = r_data['keywordList'][i]['monthlyAvePcClkCnt'] + r_data['keywordList'][i][
                'monthlyAveMobileClkCnt']
            d['rating'] = r_data['keywordList'][i]['monthlyPcQcCnt'] + r_data['keywordList'][i]['monthlyMobileQcCnt']
            d['경쟁강도'] = click / search

            # 네이버 API에서 제공하는 경쟁강도는, 다수의 광고주가 추가한 광고일수록 경쟁정도가 높게 나오며, 클릭률 및 검색수와는 무관
            l.append(d)
    except:
        # print('No data for', w)
        pass

result = json.dumps(l, ensure_ascii=False)
print(result)