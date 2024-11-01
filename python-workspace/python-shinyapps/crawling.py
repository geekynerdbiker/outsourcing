import requests
from bs4 import BeautifulSoup

url = 'https://movie.daum.net/ranking/reservation'
headers = {
	'User-Agent':'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.45 Safari/537.36'
}

response = requests.get(url, headers=headers)

soup = BeautifulSoup(response.text, 'lxml')

movieInfoList = soup.find('ol', attrs={'class':'list_movieranking'}).find_all('li')

print(''.rjust(5), end='')
print('제목'.rjust(40), end='')
print('평점'.rjust(5), end='')
print('예매율'.rjust(10), end='')
print('개봉'.rjust(10))
for movieInfo in movieInfoList:
	movieRank = movieInfo.find('span', attrs={'class':f'rank_num'})
	movieTitle = movieInfo.find('a', attrs={'class':f'link_txt'})
	movieScore = movieInfo.find('span', attrs={'class':f'txt_grade'})
	movieRate = movieInfo.find('span', attrs={'class':f'txt_num'})
	openDate = movieInfo.find('span', attrs={'class':f'txt_info'})

	print(f'{movieRank.get_text()}'.ljust(5), end='')
	print(f'{movieTitle.get_text()}'.rjust(40), end='')
	print(f'{movieScore.get_text()}'.rjust(5), end='')
	print(f'{movieRate.get_text()}'.rjust(10), end='')
	print(f'{openDate.get_text().strip()[2:]}'.rjust(10))