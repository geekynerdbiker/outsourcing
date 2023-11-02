#!/usr/bin/env python
# coding: utf-8

# In[5]:


import pandas as pd

path = input("Input file path: ")
# CSV 파일에서 데이터프레임 생성 (쉼표로 구분), 컬럼 이름 자동 인식, "null" 문자열도 결측치로 취급
df = pd.read_csv(path, na_values='null')

df = df[['변수명', '값']]
# Get column names dynamically, excluding 'subject_id'
column_names = [col for col in df.columns if col != '변수명']

# 빈값(NA)이 아닌지 여부를 계산
not_na = df[column_names].notna()

# 각 subject_id별 방문 횟수 계산
visits_per_subject = df.groupby('변수명').size()

# 각 subject_id별 빈값이 아닌 항목 수 계산
not_na_per_subject = not_na.groupby(df['변수명']).sum()

# 충실도 계산
fidelity = not_na_per_subject.div(visits_per_subject, axis=0)

# 결과 출력
print(fidelity)

# 모든 환자의 충실도 평균 계산
fidelity_mean = fidelity.mean()

# 모든 환자의 최소 충실도와 최대 충실도 계산
fidelity_min = fidelity.min()
fidelity_max = fidelity.max()
fidelity_std = fidelity.std()

# 결과를 데이터프레임으로 만들기
summary = pd.DataFrame({'Fidelity Range': fidelity_min.astype(str) + ' ~ ' + fidelity_max.astype(str), 'Standard Deviation': fidelity_std})

# 결과 출력
print(summary)

