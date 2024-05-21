import requests
from bs4 import BeautifulSoup
from datetime import datetime

url = 'https://nid.naver.com/sns.login?sns_token=HDx6hBNVvqP35gr5BUtLtcC7867k5qwy&url=https%3A%2F%2Fwww.naver.com%2F&locale=en_US'
url2 = 'https://nid.naver.com/oauth/global/initSNS?idp_cd=facebook&locale=en_US&svctype=1&postDataKey=&url=https://www.naver.com/'
login_url = 'https://www.facebook.com/login/device-based/regular/login/?login_attempt=1&lwv=101'
time = int(datetime.now().timestamp())

headers = {
    'user-agent': 'Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36',
    'origin': 'https://www.facebook.com',
    'referer': 'https://www.facebook.com/login/device-based/regular/login/?login_attempt=1&lwv=101'
}

with requests.Session() as s:
    r = s.get(url)
    soup = BeautifulSoup(r.text, "lxml")
    payload = {i['name']: i.get('value', '') for i in soup.select('input[name]')}
    payload['email'] = 'YOUR_EMAIL'
    payload['encpass'] = f'#PWD_BROWSER:0:{time}:YOUR_PASSWORD'
    payload['had_password_prefilled'] = 'true'
    payload['had_cp_prefilled'] = 'true'
    payload['prefill_source'] = 'browser_dropdown'
    payload['prefill_type'] = 'contact_point'
    payload['first_prefill_source'] = 'last_login'
    payload['first_prefill_type'] = 'contact_point'
    payload['prefill_contact_point'] = 'YOUR_EMAIL'
    payload.pop('pass')
    r = s.post(login_url, data=payload, headers=headers)
    print(r.status_code)
    print(r.url)


''' form1
azoest	"2954"
lsd	"AVoK2ypkU9U"
api_key	"293471457383333"
cancel_url	"https://nid.naver.com/oauth/global/facebookCallback?error=access_denied&error_code=200&error_description=Permissions+error&error_reason=user_denied&state=2813113020#_=_"
display	"page"
isprivate	""
return_session	""
skip_api_login	"1"
signed_next	"1"
trynum	"1"
timezone	"-540"
lgndim	"eyJ3IjoxNzkyLCJoIjoxMTIwLCJhdyI6MTczNiwiYWgiOjEwOTUsImMiOjMwfQ=="
lgnrnd	"015437_eZHa"
lgnjs	"1702374877"
email	"40792297955"
prefill_contact_point	"40792297955"
prefill_source	"browser_dropdown"
prefill_type	"password"
first_prefill_source	"last_login"
first_prefill_type	"contact_point"
had_cp_prefilled	"true"
had_password_prefilled	"true"
ab_test_data	"AAAA/AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA//AAAAAAAAB"
encpass	"#PWD_BROWSER:5:1702374883:AZRQAPwYghbrHzrXzEag9tLWxI3SstVXc+OAt8LQeHHmvBhHeiexuZUc8xYZe/DjOXyq5NRW1Jjth9hUKw1WCn9dKrXFzN6Cm3rA8eidYpi+JxRWNb9lH7Q4KcjneTbKXQ3EFsa/Bv0Xnevho8l7ClQ="
'''

''' form 2
est	"2980"
lsd	"AVoK2ypked4"
api_key	"293471457383333"
cancel_url	"https://nid.naver.com/oauth/global/facebookCallback?error=access_denied&error_code=200&error_description=Permissions+error&error_reason=user_denied&state=2745727066#_=_"
display	"page"
isprivate	""
return_session	""
skip_api_login	"1"
signed_next	"1"
trynum	"1"
timezone	"-540"
lgndim	"eyJ3IjoxNzkyLCJoIjoxMTIwLCJhdyI6MTczNiwiYWgiOjEwOTUsImMiOjMwfQ=="
lgnrnd	"020523_LhAg"
lgnjs	"1702375523"
email	"40792297955"
prefill_contact_point	"40792297955"
prefill_source	"browser_dropdown"
prefill_type	"password"
first_prefill_source	"last_login"
first_prefill_type	"contact_point"
had_cp_prefilled	"true"
had_password_prefilled	"true"
ab_test_data	"AAAA/AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA/AAAAAAAAA"
encpass "#PWD_BROWSER:5:1702375542:AZRQALU/OWFVdTGyDae1iyrsnVVYK3/OGz6oxjUjUxkIc/02EKZWAYWpb6jdLBSH0uytOxxCr4xIAosoGn3S2DSU6VrLjq0idmTUNzf4CoqP66/yaWmCBnC1FKg/aJkVmVzu2LJBZHGXDQMX2kX7990="
'''