from Investor import Investor
from DataVisualiser import DataVisualiser
from SimpleDataAnalyser import SimpleDataAnalyser

investor = Investor()
investor.run()


# 3.2
'''
sda = SimpleDataAnalyser()
sda.extract_property_info('property_information.csv')
print(len(df))
>> 118771

sda.extract_property_info('s')

>> No such file.
'''


# 3.3
'''
sda = SimpleDataAnalyser()
df = sda.extract_property_info('property_information.csv')
print(df['price'][:5])

>> 0     965000.0
>> 1     405000.0
>> 2     881000.0
>> 3    1070000.0
>> 4     500000.0
>> Name: price, dtype: float64

df = sda.currency_exchange(df, 0.5)
print(df['price'][:5])

>> 0    482500.0
>> 1    202500.0
>> 2    440500.0
>> 3    535000.0
>> 4    250000.0
>> Name: price, dtype: float64
'''

# 3.4
'''
sda = SimpleDataAnalyser()
df = sda.extract_property_info('property_information.csv')
sda.suburb_summary(df, 'Box Hill')

>> Box Hill Mean 2.4675324675324677
>> Box Hill Standard Deviation 1.2300724425499947
>> Box Hill Median 2.0
>> Box Hill Minimum 0.0
>> Box Hill Maximum 12.0

sda.suburb_summary(df, 'asd')

>> No such suburb found.
'''

# 3.5
'''
sda = SimpleDataAnalyser()
df = sda.extract_property_info('property_information.csv')
sda.avg_land_size(df, 'Box Hill')

>> Box Hill Land Size 600.8221088435374

sda.avg_land_size(df, 'asd')

>> No such suburb found.
'''

# 3.6
'''
sda = SimpleDataAnalyser()
dv = DataVisualiser()
df = sda.extract_property_info('property_information.csv')
dv.prop_val_distribution(df)
-> Create all_pvd.png with AUD

dv.prop_val_distribution(df, 'Clayton')
-> Create Clayton_pvd.png with AUD

dv.prop_val_distribution(df, 'asd')
>> No such suburb found, use 'all' as default.
-> Create all_pvd.png with AUD

dv.prop_val_distribution(df, 'Box Hill', 'usd')
-> Create Box hill_pvd.png with USD

dv.prop_val_distribution(df, 'Box Hill', 'usb')
>> No such currency found, use 'AUD' as default.
-> Create all_pvd.png with AUD
'''

# 3.7
'''
sda = SimpleDataAnalyser()
dv = DataVisualiser()
df = sda.extract_property_info('property_information.csv')
dv.sales_trend(df)
-> Create sold.png
'''

# 3.8
'''
sda = SimpleDataAnalyser()
df = sda.extract_property_info('property_information.csv')
print(sda.locate_price(133000, df, 'Clayton'))
>> True

print(sda.locate_price(133000, df, 'asd'))
>> No such suburb found.
>> None

print(sda.locate_price(845000, df, 'Clayton'))
>> False
'''