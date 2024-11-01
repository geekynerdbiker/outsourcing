import pandas as pd
import matplotlib.pyplot as plt
df = pd.read_csv('lottery.csv')

df = df[df['win'] == 1]
count = [0, 0, 0, 0, 0]

count[0] += (len(df.loc[df['first'] <= 10]))
count[1] += len(df.loc[(df['first'] > 10) & (df['first'] <= 20)])
count[2] += len(df.loc[(df['first'] > 20) & (df['first'] <= 30)])
count[3] += len(df.loc[(df['first'] > 30) & (df['first'] <= 40)])
count[4] += len(df.loc[df['first'] > 40])

count[0] += (len(df.loc[df['second'] <= 10]))
count[1] += len(df.loc[(df['second'] > 10) & (df['second'] <= 20)])
count[2] += len(df.loc[(df['second'] > 20) & (df['second'] <= 30)])
count[3] += len(df.loc[(df['second'] > 30) & (df['second'] <= 40)])
count[4] += len(df.loc[df['second'] > 40])

count[0] += (len(df.loc[df['third'] <= 10]))
count[1] += len(df.loc[(df['third'] > 10) & (df['third'] <= 20)])
count[2] += len(df.loc[(df['third'] > 20) & (df['third'] <= 30)])
count[3] += len(df.loc[(df['third'] > 30) & (df['third'] <= 40)])
count[4] += len(df.loc[df['third'] > 40])

count[0] += (len(df.loc[df['fourth'] <= 10]))
count[1] += len(df.loc[(df['fourth'] > 10) & (df['fourth'] <= 20)])
count[2] += len(df.loc[(df['fourth'] > 20) & (df['fourth'] <= 30)])
count[3] += len(df.loc[(df['fourth'] > 30) & (df['fourth'] <= 40)])
count[4] += len(df.loc[df['fourth'] > 40])

count[0] += (len(df.loc[df['fifth'] <= 10]))
count[1] += len(df.loc[(df['fifth'] > 10) & (df['fifth'] <= 20)])
count[2] += len(df.loc[(df['fifth'] > 20) & (df['fifth'] <= 30)])
count[3] += len(df.loc[(df['fifth'] > 30) & (df['fifth'] <= 40)])
count[4] += len(df.loc[df['fifth'] > 40])

count[0] += (len(df.loc[df['sixth'] <= 10]))
count[1] += len(df.loc[(df['sixth'] > 10) & (df['sixth'] <= 20)])
count[2] += len(df.loc[(df['sixth'] > 20) & (df['sixth'] <= 30)])
count[3] += len(df.loc[(df['sixth'] > 30) & (df['sixth'] <= 40)])
count[4] += len(df.loc[df['sixth'] > 40])

count[0] += (len(df.loc[df['bonus'] <= 10]))
count[1] += len(df.loc[(df['bonus'] > 10) & (df['bonus'] <= 20)])
count[2] += len(df.loc[(df['bonus'] > 20) & (df['bonus'] <= 30)])
count[3] += len(df.loc[(df['bonus'] > 30) & (df['bonus'] <= 40)])
count[4] += len(df.loc[df['bonus'] > 40])

print(count)

label=['1-10','11-20','21-30','31-40','41-45']
plt.barh(label, count)
plt.show()