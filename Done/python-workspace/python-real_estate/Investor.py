from DataVisualiser import DataVisualiser
from SimpleDataAnalyser import SimpleDataAnalyser


class Investor:  # to display a menu, ask for and process user inputs, etc.
    def __init__(self):
        self.sda = SimpleDataAnalyser()
        self.dv = DataVisualiser()

        self.df = self.sda.extract_property_info('property_information.csv')
        self.suburb_list = self.df['suburb'].unique()
        self.currency_dict = {"AUD": 1, "USD": 0.66, "INR": 54.25, "CNY":
            4.72, "JPY": 93.87, "HKD": 5.12, "KRW": 860.92, "GBP": 0.51,
                              "EUR": 0.60, "SGD": 0.88}
        self.currency_list = list(self.currency_dict.keys())

    def get_command(self):
        print('1) Get Suburb Infomation')
        print('2) See Property Sales Trend')
        print('3) Find a Property')
        print('4) Quit Program\n')

        return input('Enter command: ')

    def run(self):
        while True:
            option = self.get_command()
            if option == '1':
                print(self.suburb_list)
                while True:
                    suburb = input("\nEnter suburb name (all for 'all'): ")

                    if suburb not in self.suburb_list and suburb != 'all':
                        print('No such suburb found.')
                    else:
                        break
                self.sda.suburb_summary(self.df, suburb)
                self.sda.avg_land_size(self.df, suburb)

                print(self.currency_list)
                currency = input('Enter currency: ')

                if currency.upper() not in self.currency_list:
                    print("No such currency found, use 'AUD' as default.")
                    currency = 'AUD'
                self.dv.prop_val_distribution(self.df, suburb, currency.upper())
            elif option == '2':
                self.dv.sales_trend(self.df)
            elif option == '3':
                print(self.suburb_list)
                while True:
                    suburb = input('Enter suburb name: ')
                    if suburb not in self.suburb_list:
                        print('No such suburb found.')
                    else:
                        break

                while True:
                    price = input('Enter price: ')
                    if not price.isdigit():
                        print('Invalid input.')
                    else:
                        break

                if self.sda.locate_price(price, self.df, suburb):
                    print('\nFound price with', price, 'in', suburb + '.')
                    print()
                else:
                    print('Cannot find price with', price, 'in', suburb + '.')
                    print()

            elif option == '4':
                break
            else:
                print('Wrong command!')
