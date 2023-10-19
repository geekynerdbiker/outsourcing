class PrintResult:

    def __init__(self):
        self.__res = 0
        self.__num_moves = 0

    def set_res(self, value):
        self.__res = value

    def set_num_moves(self, value):
        self.__num_moves = value

    def print_step(self, step, player_1, player_2, table):
        print("\nfrom Print_Result After move: ", step)
        print("User 1:", player_1.get_cards_from_userview())
        print("User 2:", player_2.get_cards_from_userview())
        print("Table :", table.get_cards_from_userview(), "\n")


    def print_output(self):
        print("The Result is:")

        if self.__res == 1:
            print("Player 1 wins!")
        elif self.__res == 2:
            print("Player 2 wins!")
        else:
            print("It is a tie!")
        print("Number of moves played is ->", self.__num_moves)
