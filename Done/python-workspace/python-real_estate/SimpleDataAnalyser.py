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
                print(sub + " Bedrooms Informations")
                print(sub + " Mean", dataframe.loc[dataframe['suburb'] == sub]['bedrooms'].mean())
                print(sub + " Standard Deviation", dataframe.loc[dataframe['suburb'] == sub]['bedrooms'].std())
                print(sub + " Median", dataframe.loc[dataframe['suburb'] == sub]['bedrooms'].median())
                print(sub + " Minimum", dataframe.loc[dataframe['suburb'] == sub]['bedrooms'].min())
                print(sub + " Maximum", dataframe.loc[dataframe['suburb'] == sub]['bedrooms'].max())
                print()

                print(sub + " Bathrooms Informations")
                print(sub + " Mean", dataframe.loc[dataframe['suburb'] == sub]['bathrooms'].mean())
                print(sub + " Standard Deviation", dataframe.loc[dataframe['suburb'] == sub]['bathrooms'].std())
                print(sub + " Median", dataframe.loc[dataframe['suburb'] == sub]['bathrooms'].median())
                print(sub + " Minimum", dataframe.loc[dataframe['suburb'] == sub]['bathrooms'].min())
                print(sub + " Maximum", dataframe.loc[dataframe['suburb'] == sub]['bathrooms'].max())
                print()

                print(sub + " Parking Lots Informations")
                print(sub + " Mean", dataframe.loc[dataframe['suburb'] == sub]['parking_spaces'].mean())
                print(sub + " Standard Deviation", dataframe.loc[dataframe['suburb'] == sub]['parking_spaces'].std())
                print(sub + " Median", dataframe.loc[dataframe['suburb'] == sub]['parking_spaces'].median())
                print(sub + " Minimum", dataframe.loc[dataframe['suburb'] == sub]['parking_spaces'].min())
                print(sub + " Maximum", dataframe.loc[dataframe['suburb'] == sub]['parking_spaces'].max())
                print()
        else:
            if suburb not in dataframe['suburb'].unique():
                print("No such suburb found.")
            else:
                print(suburb + " Bedrooms Informations")
                print(suburb + " Mean", dataframe.loc[dataframe['suburb'] == suburb]['bedrooms'].mean())
                print(suburb + " Standard Deviation", dataframe.loc[dataframe['suburb'] == suburb]['bedrooms'].std())
                print(suburb + " Median", dataframe.loc[dataframe['suburb'] == suburb]['bedrooms'].median())
                print(suburb + " Minimum", dataframe.loc[dataframe['suburb'] == suburb]['bedrooms'].min())
                print(suburb + " Maximum", dataframe.loc[dataframe['suburb'] == suburb]['bedrooms'].max())
                print()

                print(suburb + " Bathrooms Informations")
                print(suburb + " Mean", dataframe.loc[dataframe['suburb'] == suburb]['bathrooms'].mean())
                print(suburb + " Standard Deviation", dataframe.loc[dataframe['suburb'] == suburb]['bathrooms'].std())
                print(suburb + " Median", dataframe.loc[dataframe['suburb'] == suburb]['bathrooms'].median())
                print(suburb + " Minimum", dataframe.loc[dataframe['suburb'] == suburb]['bathrooms'].min())
                print(suburb + " Maximum", dataframe.loc[dataframe['suburb'] == suburb]['bathrooms'].max())
                print()

                print(suburb + " Parking Lots Informations")
                print(suburb + " Mean", dataframe.loc[dataframe['suburb'] == suburb]['parking_spaces'].mean())
                print(suburb + " Standard Deviation", dataframe.loc[dataframe['suburb'] == suburb]['parking_spaces'].std())
                print(suburb + " Median", dataframe.loc[dataframe['suburb'] == suburb]['parking_spaces'].median())
                print(suburb + " Minimum", dataframe.loc[dataframe['suburb'] == suburb]['parking_spaces'].min())
                print(suburb + " Maximum", dataframe.loc[dataframe['suburb'] == suburb]['parking_spaces'].max())
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
        self.reverse_insertion_sort(price_list)

        start, end = 0, len(price_list) - 1
        result = self.recursive_binary_search(target_price, price_list, start, end)

        if not result:
            print('\nHere is price list reference.')
            print(price_list)
        return result

    def reverse_insertion_sort(self, arr):
        for end in range(1, len(arr)):
            i = end
            while i > 0 and arr[i - 1] < arr[i]:
                arr[i - 1], arr[i] = arr[i], arr[i - 1]
                i -= 1

    def recursive_binary_search(self, target_price, price_list, start, end):
        if start <= end:
            mid = (start + end) // 2
            if float(target_price) < price_list[mid]:
                return self.recursive_binary_search(target_price, price_list, mid + 1, end)
            elif float(target_price) > price_list[mid]:
                return self.recursive_binary_search(target_price, price_list, start, mid - 1)
            elif float(target_price) == price_list[mid]:
                return True
        return False
