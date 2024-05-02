from abc import ABC

from CardContainer import CardContainer
from Card import IntCard


class Node:
    def __init__(self, data):
        self.__data = data
        self.__next = None

    def get_next(self):
        return self.__next

    def set_next(self, value):
        self.__next = value

    def get_data(self):
        return self.__data


class CardsCnterUsingList(CardContainer, ABC):
    def __init__(self):
        super().__init__()
        self.__head = None

    def add_new_cards(self, lofc):
        for c in lofc:
            card = c
            node = self.__head

            if c[1] == 'A':
                card = (c[0], '14')
            elif c[1] == 'J':
                card = (c[0], '11')
            elif c[1] == 'Q':
                card = (c[0], '12')
            elif c[1] == 'K':
                card = (c[0], '13')
            else:
                card = (c[0], c[1])

            if c[0] == 'Clubs':
                card = int(card[1]) - 1
            elif c[0] == 'Diamonds':
                card = int(card[1]) - 1 + 13
            elif c[0] == 'Hearts':
                card = int(card[1]) - 1 + (13 * 2)
            elif c[0] == 'Spades':
                card = int(card[1]) - 1 + (13 * 3)

            intCard = IntCard()
            intCard.set_value(card)

            if node is None:
                self.__head = Node(intCard)
            else:
                while node.get_next() is not None:
                    node = node.get_next()
                node.set_next(Node(intCard))

    def add_new_card(self, c):
        card = c
        node = self.__head

        if node is None:
            self.__head = Node(card)
        else:
            while node.get_next() is not None:
                node = node.get_next()
            node.set_next(Node(card))

    def get_cards(self):
        cards = []
        node = self.__head

        while node is not None:
            cards.append(node.get_data().get_value())
            node = node.get_next()
        return cards

    def get_cards_from_userview(self):
        cards = []
        node = self.__head

        while node is not None:
            value = node.get_data().get_value()
            suit = ''

            if 1 <= node.get_data().get_value() <= 13:
                suit = 'Clubs'
                value += 1

                if value == 14:
                    value = 'A'
                elif value == 11:
                    value = 'J'
                elif value == 12:
                    value = 'Q'
                elif value == 13:
                    value = 'K'
                else:
                    value = str(value)

            elif 14 <= node.get_data().get_value() <= 26:
                suit = 'Diamonds'
                value -= 12

                if value == 14:
                    value = 'A'
                elif value == 11:
                    value = 'J'
                elif value == 12:
                    value = 'Q'
                elif value == 13:
                    value = 'K'
                else:
                    value = str(value)

            elif 27 <= node.get_data().get_value() <= 39:
                suit = 'Hearts'
                value -= 25

                if value == 14:
                    value = 'A'
                elif value == 11:
                    value = 'J'
                elif value == 12:
                    value = 'Q'
                elif value == 13:
                    value = 'K'
                else:
                    value = str(value)

            elif 40 <= node.get_data().get_value() <= 52:
                suit = 'Spades'
                value -= 38

                if value == 14:
                    value = 'A'
                elif value == 11:
                    value = 'J'
                elif value == 12:
                    value = 'Q'
                elif value == 13:
                    value = 'K'
                else:
                    value = str(value)

            cards.append((suit, value))
            node = node.get_next()
        return cards

    def remove_first_card(self):
        node = self.__head
        self.__head = self.__head.get_next()

        return node.get_data()

    def get_head(self):
        return self.__head
