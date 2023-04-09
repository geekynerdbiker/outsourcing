def buy_cheese(gold: int) -> tuple:
    print(f'You have {gold} gold to spend.')
    answer = input('State [cheese quantity]: #').split()

    if answer[0] == 'back':
        return 0, 0

    if answer[0].lower() != 'cheddar' or len(answer) < 2:
        print('Sorry, did not understand.')
        return 0, 0

    elif int(answer[1]) <= 0:
        print('Must purchase a positive amount of cheese.')
        return 0, 0

    elif gold < int(answer[1]) * 10:
        print('Insufficient gold.')
        return 0, 0

    else:
        print(f'Successfully purchase {int(answer[1])} cheddar.')
        return int(answer[1]) * 10, int(answer[1])


def display_inventory(gold: int, cheese: int, trap: str) -> None:
    print(f'Gold - {gold}')
    print(f'Cheddar - {cheese}')
    print(f'Trap - {trap}')


def main(gold=125, cheese=0, trap='Cardboard and Hook Trap'):
    print('''Welcome to The Cheese Shop!
Cheddar - 10 gold''')
    gold = gold
    cheese = cheese
    trap = trap

    while True:
        print(f'''\nHow can I help ye?
1. Buy cheese
2. View inventory
3. Leave shop''')

        num = int(input('#'))

        if num == 1:
            (spent_gold, get_cheese) = buy_cheese(gold)
            gold -= spent_gold
            cheese += get_cheese

        elif num == 2:
            display_inventory(gold, cheese, trap)

        elif num == 3:
            return gold, cheese

        else:
            continue


if __name__ == '__main__':
    main()
