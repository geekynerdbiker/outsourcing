import pandas as pd


class SimpleDataAnalyser:  # to deal with the loading of data as well as the simple analyses
    def extract_property_info(self, file_path):
        try:
            return pd.read_csv(file_path)
        except:
            print('No such file.')
            return None

    def currency_exchange(self, dataframe, exchange_rate):
        dataframe['price'] = dataframe['price'].mul(exchange_rate)
        return dataframe

    def suburb_summary(self, dataframe, suburb='all'):
        if suburb == 'all':
            for sub in dataframe['suburb'].unique():
                print(sub + " Mean", dataframe.loc[dataframe['suburb'] == sub]['bedrooms'].mean())
                print(sub + " Standard Deviation", dataframe.loc[dataframe['suburb'] == sub]['bedrooms'].std())
                print(sub + " Median", dataframe.loc[dataframe['suburb'] == sub]['bedrooms'].median())
                print(sub + " Minimum", dataframe.loc[dataframe['suburb'] == sub]['bedrooms'].min())
                print(sub + " Maximum", dataframe.loc[dataframe['suburb'] == sub]['bedrooms'].max())
                print()
        else:
            if suburb not in dataframe['suburb'].unique():
                print("No such suburb found.")
            else:
                print(suburb + " Mean", dataframe.loc[dataframe['suburb'] == suburb]['bedrooms'].mean())
                print(suburb + " Standard Deviation", dataframe.loc[dataframe['suburb'] == suburb]['bedrooms'].std())
                print(suburb + " Median", dataframe.loc[dataframe['suburb'] == suburb]['bedrooms'].median())
                print(suburb + " Minimum", dataframe.loc[dataframe['suburb'] == suburb]['bedrooms'].min())
                print(suburb + " Maximum", dataframe.loc[dataframe['suburb'] == suburb]['bedrooms'].max())
                print()

    def avg_land_size(self, dataframe, suburb='all'):
        if suburb == 'all':
            for sub in dataframe['suburb'].unique():
                print(sub + " Land Size",
                      dataframe.loc[dataframe['suburb'] == sub].loc[dataframe['land_size'] >= 0]['land_size'].mean())
        else:
            if suburb not in dataframe['suburb'].unique():
                print("No such suburb found.")
                return
            print(suburb + " Land Size",
                      dataframe.loc[dataframe['suburb'] == suburb].loc[dataframe['land_size'] >= 0]['land_size'].mean())

    def locate_price(self, target_price, data, target_suburb):
        if target_suburb not in data['suburb'].unique():
            print("No such suburb found.")
            return
        df = data.loc[data['suburb'] == target_suburb].dropna(subset=['price'])

        price_list = df['price'].tolist()
        price_list.sort()

        start, end = 0, len(price_list) - 1
        return self.recursive_binary_search(target_price, price_list, start, end)

    def recursive_binary_search(self, target_price, price_list, start, end):
        if start <= end:
            mid = (start + end) // 2
            if target_price > price_list[mid]:
                return self.recursive_binary_search(target_price, price_list, mid + 1, end)
            elif target_price < price_list[mid]:
                return self.recursive_binary_search(target_price, price_list, start, mid - 1)
            elif target_price == price_list[mid]:
                return True
        return False
