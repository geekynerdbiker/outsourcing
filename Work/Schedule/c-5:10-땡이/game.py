Python 3.7.6 (tags/v3.7.6:43364a7ae0, Dec 19 2019, 00:42:30) [MSC v.1916 64 bit (AMD64)] on win32
Type "help", "copyright", "credits" or "license()" for more information.
>>> import random

'''
We recommend you import your 'name', 'train' and 'shop' modules to complete this 
question. It will save trouble in needing to copy and paste code from previous 
questions. However if you wish not to, you are free to remove the imports below.
Feel free to import other modules that you have written.
'''
import name
import train
import shop


def get_game_menu():
    print(f'''1. Exit game
2. Join the Hunt
3. The Cheese Shop
4. Change Cheese''')


def change_cheese(player_name: str, trap: str, cheese: list, e_flag: bool = False) -> tuple:
    while True:
        print(f'Hunter {player_name}, you currently have:')
        print(f'Cheddar - {cheese[0][1]}')
        print(f'Marble - {cheese[1][1]}')
        print(f'Swiss - {cheese[2][1]}')
        cheese_name = input('\nType cheese name to arm trap: ')
        if cheese_name == 'back':
            print()
            return (0, change_cheese)
        
        answer = input(f'Do you want to arm your trap with {cheese_name.capitalize()}? ')
        if cheese_name.lower() == cheese[0][0].lower():
            if cheese[0][1] > 0:
                if answer.lower() == 'yes':
                    print(f'{trap} is now armed with {cheese[0][0].capitalize()}!\n')
                    return (1, cheese)
                elif answer.lower() =='no':
                    print()
                    cheese_name
                    if cheese_name.lower() == 'back':  
                        return (0,cheese)                    
                else:
                    print()
                    return (0,cheese)
            else:
                print('Out of cheese!\n')

        elif cheese_name.lower() == cheese[1][0].lower():
            if cheese[1][1] > 0:
                if answer.lower() == 'yes':
                    print(f'{trap} is now armed with {cheese[1][0].capitalize()}!\n')
                    return (1, cheese)
                elif answer.lower() =='no':
                    print()
                    cheese_name
                    if cheese_name.lower() == 'back':  
                        return (0,cheese)                    
                else:
                    print()
                    return (0,cheese)
            else:
                print('Out of cheese!\n')

        elif cheese_name.lower() == cheese[2][0].lower():
            if cheese[2][1] > 0:
                if answer.lower() == 'yes':
                    print(f'{trap} is now armed with {cheese[2][0].capitalize()}!\n')
                    return (1, cheese)
                elif answer.lower() =='no': 
                    print()
                    cheese_name
                    if cheese_name.lower() == 'back':  
                        return (0,cheese)                    
                else:
                    print()
                    return (0,cheese)
            else:
                print('Out of cheese!\n')

        else:
            print('No such cheese!\n')

    '''
    Handles the inputs and ouputs of the change cheese feature.
    Parameters:
        hunter_name: str,        the name of the player.
        trap:        str,        the trap name.
        cheese:      list,       all the cheese and its quantities the player 
                                 currently possesses.
        e_flag:      bool,       if the trap is enchanted, this will be True. 
                                 default value is False.
    Returns:
        trap_status: bool,       True if armed and False otherwise.
        trap_cheese: str | None, the type of cheese in the trap. if player 
                                 exits the function without without arming 
                                 trap succesfully, this value is None.
    '''
    pass



def main():
    print(f'''Mousehunt

       ____()()
      /      @@
`~~~~~\_;m__m._>o

Inspired by Mousehunt© Hitgrab
Programmer - An INFO1110/COMP9001 Student
Mice art - Joan Stark\n''')   

    print("What's ye name, Hunter?")
    player_name = input()
    player_gold = 125
    player_cheese = [["Cheddar", 0], ["Marble", 0], ["Swiss", 0]]
    player_point = 0
    player_trap = 'Cardboard and Hook Trap'

    if name.is_valid_name(player_name):
        print(f'Welcome to the Kingdom, Hunter {player_name}!')
    else:
        player_name = 'Bob'
        print(f'Welcome to the Kingdom, Hunter {player_name}!')

    print("Before we begin, let's train you up!")
    training = input('Press "Enter" to start training or "skip" to Start Game: ')
    print()

    if training == '':
        setup = train.main()
        print()
        player_trap = setup[0]
        while True:
            print(f'''What do ye want to do now, Hunter {player_name}?''')
            get_game_menu()
            select = input()
            select = int(select)
            if select == 1:
                break

            elif select == 2:
                count = 0
                stop = False
                while count < 5:
                    print('Sound the horn to call for the mouse...')
                    horn = input('Sound the horn by typing "yes": ')
                    if horn == 'yes':
                        if player_cheese[0][1]>0:
                            if random.random() < 0.5:
                                player_cheese[0][1] -= 1 
                                print('Caught a Brown mouse!')
                                player_gold += 125
                                player_point += 115 
                            else:
                                count += 1
                                print('Nothing happens.')


                        elif player_cheese[1][1]>0:
                            if random.random() < 0.5:
                                player_cheese[1][1] -= 1 
                                print('Caught a Brown mouse!')
                                player_gold += 125
                                player_point += 115 
                            else:
                                count += 1
                                print('Nothing happens.')


                        elif player_cheese[2][1]>0:
                            if random.random()<0.5:
                                player_cheese[2][1] -= 1 
                                print('Caught a Brown mouse!')
                                player_gold += 125
                                player_point += 115 
                            else:
                                count += 1
                                print('Nothing happens.')
                        else:
                            player_cheese[2][1] -= 1                                
                            print('Nothing happens. You are out of cheese!')

                    elif horn == 'stop hunt':
                        stop = True
                        print()
                        break

                    else:
                        print('Do nothing.')

                    if not stop:
                        print(f"My gold: {player_gold}, My points: {player_point}\n")
                    
                    if stop:
                        print()
                        break


            elif select == 3:
                gold, cheese = shop.main()
                print()
                player_gold = gold
                player_cheese = cheese
                continue

            elif select == 4:
                gold = player_gold
                cheese = player_cheese
                trap=player_trap
                e_flag = False
                trap_status, trap_cheese = change_cheese(player_name, trap, cheese, e_flag)

            else:
                break

    if training == 'skip':

        while True:
            print(f'''What do ye want to do now, Hunter {player_name}?''')
            get_game_menu()
            select = input()
            select = int(select)
            if select == 1:
                break

            elif select == 2:
                count = 0
                stop = False
                while count < 5:
                    print('Sound the horn to call for the mouse...')
                    horn = input('Sound the horn by typing "yes": ')
                    if horn == 'yes':
                        if player_cheese[0][1]>0:
                            if random.random() < 0.5:
                                player_cheese[0][1] -= 1 
                                print('Caught a Brown mouse!')
                                player_gold += 125
                                player_point += 115 
                            else:
                                count += 1
                                print('Nothing happens.')


                        elif player_cheese[1][1]>0:
                            if random.random() < 0.5:
                                player_cheese[1][1] -= 1 
                                print('Caught a Brown mouse!')
                                player_gold += 125
                                player_point += 115 
                            else:
                                count += 1
                                print('Nothing happens.')


                        elif player_cheese[2][1]>0:
                            if random.random()<0.5:
                                player_cheese[2][1] -= 1 
                                print('Caught a Brown mouse!')
                                player_gold += 125
                                player_point += 115 
                            else:
                                count += 1
                                print('Nothing happens.')
                        else:
                            player_cheese[2][1] -= 1                                
                            print('Nothing happens. You are out of cheese!')

                    elif horn == 'stop hunt':
                        stop = True
                        print()
                        break

                    else:
                        print('Do nothing.')

                    if not stop:
                        print(f"My gold: {player_gold}, My points: {player_point}\n")
                    
                    if stop:
                        print()
                        break

            elif select == 3:
                gold, cheese = shop.main()
                print()
                player_gold = gold
                player_cheese = cheese
                continue

            elif select == 4:
                gold = player_gold
                cheese = player_cheese
                trap=player_trap
                e_flag = False
                trap_status, trap_cheese = change_cheese(player_name, trap, cheese, e_flag)

            else:
                break


if __name__ == '__main__':
    main()




# you can make more functions or global read-only variables here if you please!

def get_game_menu():
    while True:
        print(f'''
What do ye want to do now, Hunter {player_name}?
1. Exit game
2. Join the Hunt
3. The Cheese Shop''')
        select=input()
        select=int(select)

def change_cheese(hunter_name: str, trap: str, cheese: list, e_flag: bool = False) -> tuple:
    '''
    Handles the inputs and ouputs of the change cheese feature.
    Parameters:
        hunter_name: str,        the name of the player.
        trap:        str,        the trap name.
        cheese:      list,       all the cheese and its quantities the player 
                                 currently possesses.
        e_flag:      bool,       if the trap is enchanted, this will be True. 
                                 default value is False.
    Returns:
        trap_status: bool,       True if armed and False otherwise.
        trap_cheese: str | None, the type of cheese in the trap. if player 
                                 exits the function without without arming 
                                 trap succesfully, this value is None.
    '''
    pass


def consume_cheese(to_eat: str, cheese: list) -> None:
    '''
    Handles the consumption of cheese.
    Will modify the cheese list, if required.
    Parameters:
        to_eat:    str,        the type of cheese to consume during the hunt.
        cheese:    list,       all the cheeses and quantities the player 
                               currently posseses.
    '''
    pass


def hunt(gold: int, cheese: list, trap_cheese: str | None, points: int) -> tuple:
    '''
    Handles the hunt mechanic.
    It includes the inputs and outputs of sounding the horn, the result of 
    the hunt, the gold and points earned, and whether users want to continue 
    after failing consecutively.
    The function will modify the cheese list, if required.
    Parameters:
        gold:        int,        the quantity of gold the player possesses.
        cheese:      list,       all the cheese and quantities the player 
                                 currently posseses.
        trap_cheese: str | None, the type of cheese that the trap is currently 
                                 armed with. if its not armed, value is None.
        points:      int,        the quantity of points that the player 
                                 currently posseses.
    Returns:
        gold:        int,        the updated quantity of gold after the hunt.   
        points:      int,        the updated quantity of points after the hunt.
    '''
    pass


def main():
    '''
    Implement your code here.
    '''
    pass


if __name__ == '__main__':
    main()