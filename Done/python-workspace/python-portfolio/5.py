import pandas as pd
import matplotlib.pyplot as plt


def extract(date):
    y = str(date.year)
    m = date.month
    d = date.day

    if m < 10:
        m = '0' + str(m)
    if d < 10:
        d = '0' + str(d)

    return y + str(m) + str(d)


def extract_m(date):
    y = str(date.year)
    m = date.month

    if m < 10:
        m = '0' + str(m)

    return y + str(m)


data = pd.read_excel("Onlineretail_France.xlsx", engine="openpyxl")
data['TotalPrice'] = data['UnitPrice'] * data['Quantity']
x = ['Dec', 'Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov']
x_month = ['Dec', 'Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov']

# 5-1
data_daily = data.set_index('InvoiceDate').groupby(extract).sum()['TotalPrice']

plt.figure()
plt.xticks(range(12))
plt.plot(data_daily)
plt.show()

# 5-2
data_monthly = data.set_index('InvoiceDate').groupby(extract_m).sum()['TotalPrice']

plt.figure()
plt.plot(x, data_monthly)
plt.show()
