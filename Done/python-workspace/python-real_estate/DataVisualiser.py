import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from SimpleDataAnalyser import SimpleDataAnalyser


class DataVisualiser:  # to deal with the visualisations
    def __init__(self):
        self.sda = SimpleDataAnalyser()

    def prop_val_distribution(self, dataframe, suburb='all', target_currency='AUD'):
        currency_dict = {"AUD": 1, "USD": 0.66, "INR": 54.25, "CNY": 4.72, "JPY": 93.87, "HKD": 5.12, "KRW": 860.92,
                         "GBP": 0.51, "EUR": 0.60, "SGD": 0.88}

        target_currency = target_currency.upper()
        if suburb == 'all':
            for sub in dataframe['suburb'].unique():
                prices = dataframe.loc[dataframe['suburb'] == sub].dropna(subset=['price'])
                try:
                    currency = currency_dict[target_currency]
                    data = self.sda.currency_exchange(prices, currency)['price']

                    plt.hist(data, alpha=0.7)

                    plt.title('Property Value Distribution')
                    plt.xlabel(target_currency)
                    plt.ylabel('Properties')

                    plt.savefig(suburb + '_pvd.png')
                except:
                    print("No such currency found, use 'AUD' as default.")
                    self.prop_val_distribution(dataframe)
        else:
            if suburb not in dataframe['suburb'].unique():
                print("No such suburb found, use 'all' as default.")
                self.prop_val_distribution(dataframe, target_currency=target_currency)
            prices = dataframe.loc[dataframe['suburb'] == suburb].dropna(subset=['price'])
            try:
                currency = currency_dict[target_currency]
                data = self.sda.currency_exchange(prices, currency)['price']

                plt.hist(data)

                plt.title('Property Value Distribution')
                plt.xlabel('Price in ' + target_currency)
                plt.ylabel('Number of properties')

                plt.savefig(suburb + '_pvd.png')
            except:
                print("No such currency found, use 'AUD' as default.")
                self.prop_val_distribution(dataframe, suburb)

    def sales_trend(self, dataframe):
        df = dataframe.dropna(subset=['sold_date'])
        df = df.copy()
        df['sold_date'] = pd.to_datetime(df['sold_date'], format="%d/%m/%Y")
        df['sold_year'] = df['sold_date'].dt.year

        years = df['sold_year'].unique()
        counts = []

        for year in years:
            counts.append(df.loc[df['sold_year'] == year]['sold_year'].count())

        plt.plot(years, counts)
        plt.title('Properties Sold Chart')
        plt.xlabel('Year')
        plt.ylabel('Number')

        plt.savefig('sold.png')
