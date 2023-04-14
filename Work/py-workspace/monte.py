import pandas as pd
import matplotlib.pyplot as plt
from statsmodels.stats.multicomp import pairwise_tukeyhsd

# 상품배치와 상품 구매 금액에 따른 관계 분석
placement_A = pd.read_csv("../../data/상품배치_A.csv", index_col="고객ID", encoding='euc-kr')
placement_B = pd.read_csv("../../data/상품배치_B.csv", engine="python", index_col="고객ID", encoding='euc-kr')
placement_C = pd.read_csv("../../data/상품배치_C.csv", engine="python", index_col="고객ID", encoding='euc-kr')

placement_A_without_zero = placement_A[placement_A['구매금액'] != 0]['구매금액'].values
placement_B_without_zero = placement_B[placement_B['구매금액'] != 0]['구매금액'].values
placement_C_without_zero = placement_C[placement_C['구매금액'] != 0]['구매금액'].values

## 상품 배치에 따른 상품 구매 금액 평균 차이 분석
kstest(placement_A_without_zero, 'norm')
kstest(placement_B_without_zero, 'norm')
kstest(placement_C_without_zero, 'norm')

A = placement_A_without_zero
B = placement_B_without_zero
C = placement_C_without_zero
leneve(placement_A_without_zero, placement_B_without_zero, placement_C_without_zero)
f_oneway(A, B, C)

Data = A.tolist() + B.tolist() + C.tolist()
Group = ['A'] * len(A) + ['B'] * len(B) + ['C'] * len(C)
len(Data), len(Group)

posthoc = pairwise_tukeyhsd(Data, Group)
print(posthoc)

# 구매여부와 상품 배치 간 독립성 파악
placement_A['상품배치'] = 'A'
placement_B['상품배치'] = 'B'
placement_C['상품배치'] = 'C'

placement = pd.concat([placement_A, placement_B, placement_C], axis=0, ignore_index=False)
placement['구매여부'] = (placement['구매금액'] != 0).astype(int)
placement.head()

cross_t = pd.crosstab(placement['상품배치'], placement['구매여부'])
cross_t
type(cross_t)

obs = cross_t.values
statistics, pvalue, dof, expected = chi2_contingency(obs, correction=True)
print(pvalue)

pd.DataFrame(expected, columns=cross_t.columns, index=cross_t.index)

# 사이트맵 구성에 따른 체류 시간 차이 분석
sitemap_A = pd.read_csv("../../data/사이트맵_A.csv", engine="python", encoding='euc-kr')
sitemap_B = pd.read_csv("../../data/사이트맵_B.csv", engine="python", encoding='euc-kr')
sitemap_C = pd.read_csv("../../data/사이트맵_C.csv", engine="python", encoding='euc-kr')

sitemap_A_time = sitemap_A['체류시간(분)'].values
sitemap_B_time = sitemap_B['체류시간(분)'].values
sitemap_C_time = sitemap_C['체류시간(분)'].values

# 사이트맵결 체류시간 평균 계산
A_mean = sitemap_A_time.mean()
B_mean = sitemap_B_time.mean()
C_mean = sitemap_C_time.mean()

# 사이트맵에 따른 체류 시간 평균 차이 분석
print("사이트 맵 A의 체류시간 평균: {}\n사이트 맵 B의 체류시간 평균: {}\n사이트 맵 C의 체류시간 평균: {}".format(round(A_mean, 3), round(B_mean, 3),
                                                                                round(C_mean, 3)))

# 평균차이 분석 시각화
plt.boxplot([sitemap_A_time, sitemap_B_time, sitemap_C_time])

kstest(sitemap_A_time, 'norm')
kstest(sitemap_B_time, 'norm')
kstest(sitemap_C_time, 'norm')
f_oneway(sitemap_A_time, sitemap_B_time, sitemap_C_time)

# 할인 쿠폰의 효과 분석
df = pd.read_csv("../../data/할인쿠폰발행효과.csv", engine="python", encoding='euc-kr')

# 발행후와 전의 구매 횟수 차이에 대한 기술 통계
# 발행전, 발행후의구매 횟수에 대한 시각화
# 차이 유의성 검정
plt.boxplot([df['발행전 구매 횟수'], df['발행후 구매 횟수']])
plt.xticks([1, 2], ['발행전', '발행후'])
plt.ylabel("구매 횟수")

# 체류 시간과 구매 금액 간 관계 분석
df = pd.read_csv("../../data/체류시간_구매금액.csv", engine="python", encoding='euc-kr')
df.plot(kind='scatter', x='체류시간', y='구매금액')

# 구매버튼 배치에 따른 구매율 차이 분석
df = pd.read_excel("../../data/AB테스트/구매여부_버튼타입_통계.xlsx")
df.fillna(method='ffill', inplace=True)
print(df)

# 현 데이터와 결합할 수 있는 다른 데이터를 찾아보고 데이터 결합 후 시각화 분석
cross_table = pd.crosstab([df['구매여부'], df['버튼타입']], df['고객 수'])
print(cross_table)

obs = cross_table.values
print(obs)

obs = cross_table.values
statistics, pvalue, dof, expected = chi2_contingency(obs, correction=False)
print(pvalue)
