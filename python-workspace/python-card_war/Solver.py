class Solver():
    def __init__(self):
        self.__player_1 = None
        self.__player_2 = None
        self.__table = None
        self.__print_result = None

    def set_print_result(self, print_result):
        self.__print_result = print_result

    def solve(self):
        step = 0

        while True:
            if self.__player_1.get_head() is None and self.__player_2.get_head() is None:
                return 0, step
            if self.__player_1.get_head() is None:
                return 2, step
            elif self.__player_2.get_head() is None:
                return 1, step

            self.__print_result.print_step(step, self.__player_1, self.__player_2, self.__table)

            step += 1

            card_1 = self.__player_1.remove_first_card()
            card_2 = self.__player_2.remove_first_card()

            self.__table.add_new_card(card_1)
            self.__table.add_new_card(card_2)

            if card_1.isLargerThan(card_2):
                while self.__table.get_head() is not None:
                    self.__player_1.add_new_card(self.__table.remove_first_card())
            elif card_2.isLargerThan(card_1):
                while self.__table.get_head() is not None:
                    self.__player_2.add_new_card(self.__table.remove_first_card())

    def set_playerOne(self, player_1):
        self.__player_1 = player_1

    def set_playerTwo(self, player_2):
        self.__player_2 = player_2

    def set_table(self, tbl):
        self.__table = tbl
