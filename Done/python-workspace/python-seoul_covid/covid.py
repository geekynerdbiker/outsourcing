import json
import matplotlib
from matplotlib import pyplot as plt

with open('data.json', 'r') as f:
    data = json.load(f)

s_dt = []
s_hj = []  # 서울시 확진자 누계
sn_hj = []  # 서울시 일일 확진
s_death = []  # 서울시 사망자 누계
day_death = []  # 서울시 일일 사망

for line in data['DATA']:
    date = line['s_dt'][:10].replace('.', '')
    if int(date) % 100 == 1:
        s_dt.append(date)
        s_hj.append(int(line['s_hj']))
        sn_hj.append(int(line['sn_hj']))
        s_death.append(int(line['s_death']))
        if line['day_death'] is not None:
            day_death.append(int(line['day_death']))
        else:
            day_death.append(0)

s_dt.reverse()
s_hj.reverse()
sn_hj.reverse()
s_death.reverse()
day_death.reverse()
matplotlib.rcParams['font.family'] ='Malgun Gothic'
matplotlib.rcParams['axes.unicode_minus'] =False


# 서울시 확진자 누계 변화
plt.figure(figsize=(10, 8))
plt.plot(s_dt, s_hj)
plt.xticks(rotation=90)
plt.yticks([_ * 100000 for _ in range(40)], [_ * 100000 for _ in range(40)])
current_values = plt.gca().get_yticks()
plt.gca().set_yticklabels(['{:.0f}'.format(x) for x in current_values])
plt.title('서울시 확진자 누계 변화')
# plt.plot(s_dt)
plt.show()

# 서울시 일일 확진 현황
plt.figure(figsize=(10, 4))
plt.plot(s_dt, sn_hj)
plt.xticks(rotation=90)
plt.yticks([_ * 5000 for _ in range(10)], [_ * 5000 for _ in range(10)])
current_values = plt.gca().get_yticks()
plt.gca().set_yticklabels(['{:.0f}'.format(x) for x in current_values])
plt.title('서울시 일일 확진 현황')
# plt.plot(s_dt)
plt.show()

# 서울시 사망자 누계 변화
plt.figure(figsize=(10, 7))
plt.plot(s_dt, s_death)
plt.xticks(rotation=90)
plt.yticks([_ * 200 for _ in range(30)], [_ * 100 for _ in range(30)])
current_values = plt.gca().get_yticks()
plt.gca().set_yticklabels(['{:.0f}'.format(x) for x in current_values])
plt.title('서울시 사망자 누계 변화')
# plt.plot(s_dt)
plt.show()

# 서울시 일일 사망 현황
plt.figure(figsize=(10, 4))
plt.plot(s_dt, day_death)
plt.xticks(rotation=90)
plt.yticks([_ * 5 for _ in range(12)], [_ * 5 for _ in range(12)])
current_values = plt.gca().get_yticks()
plt.gca().set_yticklabels(['{:.0f}'.format(x) for x in current_values])
plt.title('서울시 일일 사망 현황')
# plt.plot(s_dt)
plt.show()

