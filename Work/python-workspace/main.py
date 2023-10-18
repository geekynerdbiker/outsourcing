import pandas as pd


class SimpleDataAnalyser:  # to deal with the loading of data as well as the simple analyses
    def __init__(self):
        super()

    def extract_property_info(self, file_path):
        return pd.read_csv(file_path)

    def currency_exchange(self, dataframe, exchange_rate):
        dataframe['price'] = dataframe['price'].mul(exchange_rate)
        return dataframe

    def suburb_summary(self, dataframe, suburb='all'):
        # bedrooms_mean
        # bedrooms_std
        # bedrooms_median
        # bedrooms_min
        # bedrooms_max
        #
        # bathrooms_mean
        # bathrooms_std
        # bathrooms_median
        # bathrooms_min
        # bathrooms_max
        #
        # parking_spaces_mean
        # parking_spaces_std
        # parking_spaces_median
        # parking_spaces_min
        # parking_spaces_max

        if suburb == 'all':
            for sub in dataframe['suburb'].unique():
                print(sub + " Mean", df.loc[dataframe['suburb'] == sub]['bedrooms'].mean())
                print(sub + " Standard Deviation", df.loc[dataframe['suburb'] == sub]['bedrooms'].std())
                print(sub + " Median", df.loc[dataframe['suburb'] == sub]['bedrooms'].median())
                print(sub + " Minimum", df.loc[dataframe['suburb'] == sub]['bedrooms'].min())
                print(sub + " Maximum", df.loc[dataframe['suburb'] == sub]['bedrooms'].max())
                print()
        else:
            if suburb not in dataframe['suburb'].unique():
                print("No suburb named", suburb)
            else:
                print(suburb + " Mean", df.loc[dataframe['suburb'] == suburb]['bedrooms'].mean())
                print(suburb + " Standard Deviation", df.loc[dataframe['suburb'] == suburb]['bedrooms'].std())
                print(suburb + " Median", df.loc[dataframe['suburb'] == suburb]['bedrooms'].median())
                print(suburb + " Minimum", df.loc[dataframe['suburb'] == suburb]['bedrooms'].min())
                print(suburb + " Maximum", df.loc[dataframe['suburb'] == suburb]['bedrooms'].max())
                print()


class DataVisualiser:  # to deal with the visualisations
    pass


class Investor:  # to display a menu, ask for and process user inputs, etc.
    pass


sda = SimpleDataAnalyser()
df = sda.extract_property_info('property_information.csv')

sda.suburb_summary(df, 'Clayton')
