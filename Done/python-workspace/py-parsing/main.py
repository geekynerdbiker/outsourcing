class continent:
    def __init__(self, name):
        self.name = name
        self.currency = ''
        self.rate = 0
        self.time = 0
        self.lang_main = ''
        self.lang_most = ''
        self.countries = []

    def update(self, currency, rate, time, lang_main, lang_most, country):
        self.currency = currency
        self.rate = rate
        self.time = time
        self.lang_main = lang_main
        self.lang_most = lang_most
        self.countries.append(country)

    def add_country(self, country):
        self.countries.append(country)

    def get_name(self, name):
        return True if self.name == name else False

    def print(self):
        print('Name of Continent: ' + self.name)
        print('Currency: ' + self.currency)
        print('Literacy Rate: ' + self.rate)
        print('Time Zone: ' + self.time)
        print('Main Language: ' + self.lang_main)
        print('Most Spoken Language: ' + self.lang_most)
        print('Countries: ')

        for i in self.countries:
            print(' ' + i)
        print()


def find_name(line_parts):
    """Find the name of the country from the list of strings."""
    return line_parts[0]


def find_currency(line_parts):
    """Find the currency of the country from the list of strings."""
    return line_parts[1]


def find_literacy_rate(line_parts):
    """Find the literacy rate of the country from the list of strings."""
    return line_parts[2]


def find_time_zone(line_parts):
    """Find the time zone of the country from the list of strings."""
    return line_parts[3]


def find_continent(line_parts):
    """Find the continent of the country from the list of strings."""
    return line_parts[4]


def find_main_language(line_parts):
    """Find the main language of the country from the list of strings."""
    return line_parts[5]


def find_most_spoken_language(line_parts):
    """Find the most spoken language of the country from the list of strings."""
    return line_parts[5] if len(line_parts) == 6 else line_parts[6]


def parse_input_file(input_file):
    """Open the input text file and parse input line by line and get details using the above mentioned
    functions. This Function outputs the sorted list as seen in the sample output"""
    data = open(input_file, 'r')

    africa = continent('Africa')
    asia = continent('Asia')
    europe = continent('Europe')
    north_america = continent('North America')
    south_america = continent('South America')

    while True:
        line = data.readline()
        if not line:
            break
        line = line.split(', ')
        line[len(line) - 1] = line[len(line) - 1].replace('\n', '')

        cont_name = find_continent(line)

        if cont_name == 'Africa':
            if africa.currency == '':
                africa.update(find_currency(line), find_literacy_rate(line), find_time_zone(line),
                              find_main_language(line), find_most_spoken_language(line), find_name(line))
            else:
                africa.add_country(find_name(line))

        elif cont_name == 'Asia':
            if asia.currency == '':
                asia.update(find_currency(line), find_literacy_rate(line), find_time_zone(line),
                            find_main_language(line), find_most_spoken_language(line), find_name(line))
            else:
                asia.add_country(find_name(line))

        elif cont_name == 'Europe':
            if europe.currency == '':
                europe.update(find_currency(line), find_literacy_rate(line), find_time_zone(line),
                              find_main_language(line), find_most_spoken_language(line), find_name(line))
            else:
                europe.add_country(find_name(line))

        elif cont_name == 'North America':
            if north_america.currency == '':
                north_america.update(find_currency(line), find_literacy_rate(line), find_time_zone(line),
                                     find_main_language(line), find_most_spoken_language(line), find_name(line))
            else:
                north_america.add_country(find_name(line))

        elif cont_name == 'South America':
            if south_america.currency == '':
                south_america.update(find_currency(line), find_literacy_rate(line), find_time_zone(line),
                                     find_main_language(line), find_most_spoken_language(line), find_name(line))
            else:
                south_america.add_country(find_name(line))

    return africa, asia, europe, north_america, south_america


continents = parse_input_file('data.txt')

for c in continents:
    c.print()
