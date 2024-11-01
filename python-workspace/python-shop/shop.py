def buy_cheese(gold: int) -> tuple:
    print('You have ' + str(gold) + ' gold to spend.')
    answer = input('State [cheese quantity]: #')
    if answer == 'back':
        return 0, 0

    cheese, quantity = answer.split(' ')
    quantity = int(quantity)

    if cheese.lower() != 'cheddar':
        print('Sorry, did not understand.')
        return 0, 0
    elif quantity < 0:
        print('Must purchase a positive amount of cheese.')
        return 0, 0
    elif gold < quantity * 10:
        print('Insufficient gold.')
        return 0, 0
    else:
        print('Successfully purchase ' + str(quantity) + ' cheddar.')
        return quantity * 10, quantity


def display_inventory(gold: int, cheese: int, trap: str) -> None:
    print('Gold - ' + str(gold))
    print('Cheddar - ' + str(cheese))
    print('Trap - ' + trap)


def main():
    print('Welcome to The Cheese Shop!')
    print('Cheddar - 10 gold')
    gold = 125
    cheddar = 0
    trap = 'Cardboard and Hook Trap'

    while True:
        print('\nHow can I help ye?')
        print('1. Buy Cheese')
        print('2. View Inventory')
        print('3. Leave Shop')

        answer = int(input('#'))

        if answer == 1:
            spent, buy = buy_cheese(gold)
            gold -= spent
            cheddar += buy
        elif answer == 2:
            display_inventory(gold, cheddar, trap)
        elif answer == 3:
            break
        else:
            continue


if __name__ == '__main__':
    main()
