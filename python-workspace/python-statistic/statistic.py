import pandas as pd
from scipy import stats
import statsmodels.api as sm

# 데이터 불러오기

survey = pd.read_csv("survey1_utf-8.csv")

# t-검정
boys = survey[survey['성별'] == '남자']
girls = survey[survey['성별'] == '여자']
rst = [stats.levene(boys.성적, girls.성적)
    , stats.levene(boys.전공선택동기, girls.전공선택동기)
    , stats.levene(boys.전공만족, girls.전공만족)
    , stats.levene(boys.학업적응, girls.학업적응)
    , stats.levene(boys.사회적지지, girls.사회적지지)
    , stats.levene(boys.대학만족, girls.대학만족)
    , stats.levene(boys.중도탈락의도, girls.중도탈락의도)]
print('------------------t-검정------------------')
print('남자 vs 여자')
for i in rst:
    print('p=' + str(i[1]))

junior = survey[survey['학년'] == '저학년']
senior = survey[survey['학년'] == '고학년']
rst = [stats.levene(junior.성적, senior.성적)
    , stats.levene(junior.전공선택동기, senior.전공선택동기)
    , stats.levene(junior.전공만족, senior.전공만족)
    , stats.levene(junior.학업적응, senior.학업적응)
    , stats.levene(junior.사회적지지, senior.사회적지지)
    , stats.levene(junior.대학만족, senior.대학만족)
    , stats.levene(junior.중도탈락의도, senior.중도탈락의도)]
print('저학년 vs 고학년')
for i in rst:
    print('p=' + str(i[1]))

nats = survey[survey['계열'] == '자연공학']
socs = survey[survey['계열'] == '인문사회예체능']
rst = [stats.levene(nats.성적, socs.성적)
    , stats.levene(nats.전공선택동기, socs.전공선택동기)
    , stats.levene(nats.전공만족, socs.전공만족)
    , stats.levene(nats.학업적응, socs.학업적응)
    , stats.levene(nats.사회적지지, socs.사회적지지)
    , stats.levene(nats.대학만족, socs.대학만족)
    , stats.levene(nats.중도탈락의도, socs.중도탈락의도)]
print('자연공학 vs 인문사회예체능')
for i in rst:
    print('p=' + str(i[1]))

# 상관분석
print('\n------------------상관분석------------------')
x_data = survey[['성적', '전공선택동기', '전공만족', '학업적응', '사회적지지', '대학만족', '중도탈락의도']]
print(x_data.corr())

# 다중회귀분석
print('\n------------------다중회귀분석------------------')
survey_data = survey.drop(['중도탈락의도'], axis=1)

target = survey[['중도탈락의도']]
x_data = survey[['성적', '전공선택동기', '전공만족', '학업적응', '사회적지지', '대학만족']]

x_data1 = sm.add_constant(x_data, has_constant="add")

multi_model = sm.OLS(target, x_data1)
fitted_multi_model = multi_model.fit()

print(fitted_multi_model.summary())
