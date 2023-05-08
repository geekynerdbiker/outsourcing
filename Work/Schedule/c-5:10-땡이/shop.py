Python 3.7.6 (tags/v3.7.6:43364a7ae0, Dec 19 2019, 00:42:30) [MSC v.1916 64 bit (AMD64)] on win32
Type "help", "copyright", "credits" or "license()" for more information.
>>> CHEESE_MENU = (("Cheddar", 10), ("Marble", 50), ("Swiss", 100))

# you can make more functions or global read-only variables here if you please!

def buy_cheese(gold: int) -> tuple:
    get_cheese =(0,0,0)
    spent_gold = 0
    while True:
        print(f'You have {gold} gold to spend.')
        answer = input('State [cheese quantity]: ').split()  

        if answer[0].lower() == 'back':
            return (spent_gold, get_cheese)

        if answer[0].lower() != 'cheddar' and answer[0].lower()!='marble' and answer[0].lower()!='swiss' :
            print(f"We don't sell {answer[0]}!")

        elif len(answer) < 2:
            print('Missing quantity.')

        elif answer[0].lower() == 'cheddar':
            try:
                quantity = int(answer[1])
            except ValueError:
                print('Invalid quantity.')
                continue

            if 10 * quantity > gold:
                print('Insufficient gold.')
                continue

            elif quantity <= 0:
                print('Must purchase positive amount of cheese.')
                continue

            else:
                gold -= 10 * quantity
                get_cheese = (get_cheese[0] + quantity, get_cheese[1], get_cheese[2])
                spent_gold += 10 * quantity
                print(f'Successfully purchase {quantity} cheddar.')
                continue

        elif answer[0].lower() == 'marble':
            try:
                quantity = int(answer[1])
            except ValueError:
                print('Invalid quantity.')
                continue

            if 50 * quantity > gold:
                print('Insufficient gold.')              
                continue
            
            elif quantity <= 0:
                print('Must purchase positive amount of cheese.')
                continue
            
            else:
                gold -= 50 * quantity
                get_cheese = (get_cheese[0], get_cheese[1] + quantity, get_cheese[2])
                spent_gold += 50 * quantity
                print(f'Successfully purchase {quantity} marble.')
                continue

        elif answer[0].lower() == 'swiss':
            try:
                quantity = int(answer[1])
            except ValueError:
                print('Invalid quantity.')
                continue
                
            if 100 * quantity > gold:
                print('Insufficient gold.')
                continue

            elif quantity <= 0:
                print('Must purchase positive amount of cheese.')
                continue
            
            else:
                gold -= 100 * quantity
                get_cheese = (get_cheese[0], get_cheese[1], get_cheese[2] + quantity)
                spent_gold += 100 * quantity
                print(f'Successfully purchase {quantity} swiss.')
                continue
        else:
            continue
    return (spent_gold, get_cheese)

    '''
    Feature for players to buy cheese from shop.
    Parameters:
        gold:           int,    amount of gold that player has
    Returns:
        gold_spent:     int,    amount of gold spent
        cheese_bought:  tuple,  amount of each type of cheese bought
    '''
    pass


def display_inventory(gold: int, cheese: list, trap: str) -> None:
    print(f"Gold - {gold}")
    print(f"Cheddar - {cheese[0][1]}")
    print(f"Marble - {cheese[1][1]}")
    print(f"Swiss - {cheese[2][1]}")
    print(f"Trap - {trap}")

    '''
    Displays contents of inventory.
    Parameters:
        gold:   int,  amount of gold that player has
        cheese: list, amount of each type of cheese that player has
        trap:   str,  name of trap that player that player has
    '''
    pass


def main():
    gold = 125
    cheese = [["Cheddar", 0], ["Marble", 0], ["Swiss", 0]]
    trap = 'Cardboard and Hook Trap'
    print('''Welcome to The Cheese Shop!
Cheddar - 10 gold
Marble - 50 gold
Swiss - 100 gold''')

    while True:
        print(f'''\nHow can I help ye?
1. Buy cheese
2. View inventory
3. Leave shop''')

        num = input()
        num = int(num)

        if num == 1:
            (spent_gold, get_cheese) = buy_cheese(gold) 
            gold-=spent_gold
            cheese[0][1] += get_cheese[0]
            cheese[1][1] += get_cheese[1]
            cheese[2][1] += get_cheese[2]

        elif num == 2:
            display_inventory(gold, cheese, trap)

        elif num == 3:
            return gold, cheese

        else:
            continue

if __name__ == "__main__":
    main() 