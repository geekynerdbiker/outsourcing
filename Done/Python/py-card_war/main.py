import sys
from CardsCnterUsingList import CardsCnterUsingList
from Solver import Solver
from PrintResult import PrintResult


def read_file_input(player_1, player_2, f_name):
    try:
        with open(f_name) as my_file:
            all_cards = my_file.readlines()
        p1_lofc = []
        p2_lofc = []
        for line in all_cards:
            p1_lofc.append((line.split(" ")[0].split(",")[0], line.split(" ")[0].split(",")[1]))
            p2_lofc.append((line.split(" ")[1].split(",")[0], line.split(" ")[1].split(",")[1].strip("\n")))
        player_1.add_new_cards(p1_lofc)
        player_2.add_new_cards(p2_lofc)

    except:
        print("File not found")
        sys.exit(1)


if __name__ == '__main__':
    file_name = input("Please enter the input file for player1 and player2 cards to play War\n")

    p1 = CardsCnterUsingList()
    p2 = CardsCnterUsingList()

    read_file_input(p1, p2, file_name)

    table = CardsCnterUsingList()

    solve = Solver()
    solve.set_playerOne(p1)
    solve.set_playerTwo(p2)
    solve.set_table(table)
    result = PrintResult()
    solve.set_print_result(result)
    res, num_moves = solve.solve()
    result.set_res(res)
    result.set_num_moves(num_moves)
    print("Game Over!\n")
    result.print_output()
