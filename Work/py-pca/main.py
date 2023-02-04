import pandas as pd
import numpy as np

from PCA_Main import PCA
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA as sk
from sklearn import decomposition
from sklearn.preprocessing import StandardScaler

df1 = pd.read_csv('data.csv')
df1_ = df1.drop(columns=['Time'], axis=1)
train = df1_.values

df2 = pd.read_csv('trouble.csv')
df2_ = df2.drop(columns=['Time'], axis=1)
test = df2_.values


std_df1 = StandardScaler().fit_transform(df1_)
std_df1 = pd.DataFrame(std_df1, index=df1_.index, columns=df1_.columns)

std_df2 = StandardScaler().fit_transform(df2_)
std_df2 = pd.DataFrame(std_df2, index=df2_.index, columns=df2_.columns)

x_train = std_df1
x_test = std_df2

# print(np.mean(x_train))


comps = 15
pca = sk(n_components=comps)
pc = pca.fit_transform(x_train)
pc_df = pd.DataFrame(data=pc, columns=[f"pca{num + 1}" for num in range(comps)])
print(pc_df)

result = pd.DataFrame({'설명 가능한 분산 비율': pca.explained_variance_, '기여율': pca.explained_variance_ratio_},
                      index=np.array([f"pca{num + 1}" for num in range(comps)]))
result['누적기여율'] = result['기여율'].cumsum()
print(result)

component_num = np.arange(1, comps+1)
component_num_1 = np.arange(0, comps+1)

plt.figure(figsize=(15, 10))
plt.title('Explainable Variance')
plt.xlabel('Number of Principal Components')
plt.ylabel('Explainable Variance')
plt.xticks(component_num_1)
plt.plot(component_num, result['설명 가능한 분산 비율'])

pca = PCA(num_comp=comps, alpha_tsq=0.95, alpha_spe=0.95)
Tsq_thres, SPE_thres = pca.fit(x_train)
Tsq, SPE = pca.predict(x_test)

print(Tsq_thres)
print(Tsq)
print(SPE_thres)
print(SPE)

plt.figure()
plt.subplot(2, 1, 1)
plt.plot(Tsq)
plt.title('Tsq(alpha=0.99)')
plt.xlabel('Time')
plt.ylabel('T-square Value')
plt.axhline(y=Tsq_thres, color='r', linestyle='--')

plt.subplots_adjust(hspace=0.7)
plt.subplot(2, 1, 2)
plt.plot(SPE)
plt.title('SPE(alpha=0.99)')
plt.xlabel('Time')
plt.ylabel('Q-square value')
plt.axhline(y=SPE_thres, color='r', linestyle='--')
plt.show()

final = []
for a in range(0, 1000):
    if Tsq[a] > Tsq_thres or SPE[a] > SPE_thres:
        i = 1
    else:
        i = 0
    final.append(i)

rst = pd.DataFrame(final)
print(rst)

# rst.columns = ['이상치여부']
# rst.to_csv('Answer.csv')