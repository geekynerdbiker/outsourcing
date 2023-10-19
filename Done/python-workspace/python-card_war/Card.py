class Card:
    def __init__(self):
        pass

    def isLargerThan(self, c):
        pass

    def print_card(self):
        pass


class IntCard(Card):
    def __init__(self):
        super().__init__()
        self.__value = None

    def set_value(self, card):
        self.__value = card

    def isLargerThan(self, c):
        return (self.__value - 1) % 13 > (c.get_value() - 1) % 13

    def get_value(self):
        return self.__value
