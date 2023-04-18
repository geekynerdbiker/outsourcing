
import os
import pandas as pd
import numpy as np

# In[27]:


from scipy.stats import *

# get_ipython().run_line_magic('precision', '3')
# np.random.seed(1111)

# In[28]:


from IPython.core.interactiveshell import InteractiveShell

InteractiveShell.ast_node_interactivity = "all"

# ### 현황분석 - 시계열 그래프로 파악

# In[2]:


df = pd.read_csv("data/일별현황데이터.csv", engine="python", encoding='utf-8')
df

# In[8]:


df.info()

# In[9]:


df.describe()

# In[3]:


# get_ipython().run_line_magic('matplotlib', 'inline')
import matplotlib.pyplot as plt

placement_A = pd.read_csv("data/상품배치_A.csv", index_col="고객ID", encoding='utf-8')
placement_A.head()
placement_A.tail()

# In[5]:


placement_B = pd.read_csv("data/상품배치_B.csv", engine="python", index_col="고객ID", encoding='utf-8')
placement_B.head()
placement_B.tail()

# In[22]:


placement_C = pd.read_csv("data/상품배치_C.csv", engine="python", index_col="고객ID", encoding='utf-8')
placement_C.head()
placement_C.tail()

# 구매금액이 0인 사람을 제외한 분석 수행

# In[23]:


# 구매금액이 0이 아닌 고객에 대해 구매 금액만 추출하시오 -> 조건인덱스, value 추출
placement_A_without_zero = placement_A[placement_A['구매금액'] != 0]['구매금액'].values
placement_B_without_zero = placement_B[placement_B['구매금액'] != 0]['구매금액'].values
placement_C_without_zero = placement_C[placement_C['구매금액'] != 0]['구매금액'].values

# In[39]:


# placement_A_without_zero


# In[8]:


# 위 세 데이터를 box plot 으로 시각화 하시오
plt.boxplot([placement_A_without_zero, placement_B_without_zero, placement_C_without_zero])

# In[ ]:


## 세 데이터의 평균이 차이가 있는지 확인하시오


# In[29]:


kstest(placement_A_without_zero, 'norm')
kstest(placement_B_without_zero, 'norm')
kstest(placement_C_without_zero, 'norm')

# In[36]:


A = placement_A_without_zero
B = placement_B_without_zero
C = placement_C_without_zero
# leneve(placement_A_without_zero, placement_B_without_zero, placement_C_without_zero)

# In[37]:


f_oneway(A, B, C)

# In[38]:


# 사후 분석

from statsmodels.stats.multicomp import pairwise_tukeyhsd

Data = A.tolist() + B.tolist() + C.tolist()  # 배열이 아니라 리스트로 변환해야 함
Group = ['A'] * len(A) + ['B'] * len(B) + ['C'] * len(C)
len(Data), len(Group)

posthoc = pairwise_tukeyhsd(Data, Group)

print(posthoc)

# 구매금액 0을 포함하여 분석 - 구매금액이 없는 사람도 포함해서 그룹별 구매금액에 차이가 있나 확인

# ####  구매 여부와 상품 배치 간 관계 파악
#

# In[39]:


# 데이터 변환
placement_A['상품배치'] = 'A'
placement_B['상품배치'] = 'B'
placement_C['상품배치'] = 'C'

placement = pd.concat([placement_A, placement_B, placement_C], axis=0, ignore_index=False)
placement['구매여부'] = (placement['구매금액'] != 0).astype(int)  # T면 1로 F면 0으로 - 구매금액이 있으면 1 없으면 0
placement.head()

# In[41]:


# 교차 테이블 생성
cross_t = pd.crosstab(placement['상품배치'], placement['구매여부'])
cross_t
type(cross_t)

# In[43]:


obs = cross_t.values
statistics, pvalue, dof, expected = chi2_contingency(obs, correction=True)
print(pvalue)  # pvalue가 0.06으로 구매여부와 상품배치에는 관계가 있다고 보기 힘듦- B랑 C가 차이가 크지 않아서 이렇게 나왔을 가능성이 큼

# In[46]:


# 기대값
pd.DataFrame(expected, columns=cross_t.columns, index=cross_t.index)

# ####  사이트맵 구성에 따른 체류 시간 차이 분석

# In[51]:


sitemap_A = pd.read_csv("data/사이트맵_A.csv", engine="python", encoding='utf-8')
sitemap_A.head()

# In[52]:


sitemap_B = pd.read_csv("data/사이트맵_B.csv", engine="python", encoding='utf-8')
sitemap_B.head()

# In[54]:


sitemap_C = pd.read_csv("data/사이트맵_C.csv", engine="python", encoding='utf-8')
sitemap_C.head()

# In[55]:


sitemap_A_time = sitemap_A['체류시간(분)'].values
sitemap_B_time = sitemap_B['체류시간(분)'].values
sitemap_C_time = sitemap_C['체류시간(분)'].values

# In[56]:


A_mean = sitemap_A_time.mean()
B_mean = sitemap_B_time.mean()
C_mean = sitemap_C_time.mean()

print("사이트 맵 A의 체류시간 평균: {}\n사이트 맵 B의 체류시간 평균: {}\n사이트 맵 C의 체류시간 평균: {}".format(round(A_mean, 3), round(B_mean, 3),
                                                                                round(C_mean, 3)))

# In[60]:


# box 플롯으로 시각화
plt.boxplot([sitemap_A_time, sitemap_B_time, sitemap_C_time])

# In[61]:


# 각 데이터가 정규분포를 따름을 확인
kstest(sitemap_A_time, 'norm')
kstest(sitemap_B_time, 'norm')
kstest(sitemap_C_time, 'norm')

# In[62]:


# 일원분산분석 수행: p-value가 거의 0에 수렴 => A, B, C의 평균은 유의한 차이가 존재하지 않음을 확인
f_oneway(sitemap_A_time, sitemap_B_time, sitemap_C_time)

# - 할인 쿠폰의 효과 분석 - 쌍체표본 T 검정

# In[63]:


df = pd.read_csv("data/할인쿠폰발행효과.csv", engine="python", encoding='utf-8')
df.head()

# In[64]:


plt.boxplot([df['발행전 구매 횟수'], df['발행후 구매 횟수']])
plt.xticks([1, 2], ['발행전', '발행후'])
plt.ylabel("구매 횟수")

# ####  체류 시간과 구매 금액 간 관계 분석 - 상관분석

# In[65]:


df = pd.read_csv("data/체류시간_구매금액.csv", engine="python", encoding='utf-8')
df.head()

# In[66]:


df.plot(kind='scatter', x='체류시간', y='구매금액')

# #### 구매버튼 배치에 따른 구매율 차이 분석

# In[67]:


df = pd.read_excel("data/구매여부_버튼타입_통계.xlsx")
df.head()

# In[71]:


df.fillna(method='ffill', inplace=True)
df

# In[82]:


cross_table = pd.crosstab([df['구매여부'], df['버튼타입']], df['고객 수'])
cross_table

# In[73]:


obs = cross_table.values
obs

# In[83]:


obs = cross_table.values  # 분석
statistics, pvalue, dof, expected = chi2_contingency(obs, correction=False)
pvalue
