import name
import train
import shop


def main():
    title = 'Mousehunt'
    logo = '''
       ____()()
      /      @@
`~~~~~\_;m__m._>o'''
    author = 'An INFO1110/COMP9001 Student'
    credits = f'''
Inspired by Mousehunt© Hitgrab
Programmer - {author}
Mice art - Joan Stark'''

    print(title)
    print(logo)
    print(credits)
    print()
    print("What's ye name, Hunter?")
    player_name = input()
    player_gold = 125
    player_cheese = 0
    player_point = 0
    player_trap = 'Cardboard and Hook Trap'

    if name.is_valid_name(player_name):
        print(f'Welcome to the Kingdom, Hunter {player_name}!')

    else:
        player_name = 'Bob'
        print(f'Welcome to the Kingdom, Hunter {player_name}!')

    print("Before we begin, let's train you up!")
    tutorial = input('Press "Enter" to start training or "skip" to Start Game: ')
    print()

    if tutorial == '':
        setup = train.main()
        player_trap = setup[0]

        while True:
            print(f'''
What do ye want to do now, Hunter {player_name}?
1. Exit game
2. Join the Hunt
3. The Cheese Shop''')
            select = input()
            select = int(select)

            if select == 1:
                break

            elif select == 2:
                count = 0
                while True:
                    print('Sound the horn to call for the mouse...')
                    horn = input('Sound the horn by typing "yes": ')
                    if horn == 'yes':
                        if player_cheese > 0:
                            if random.random() < 0.5:
                                count = 0
                                player_cheese -= 1
                                print('Caught a Brown mouse!')
                                player_gold += 125
                                player_point += 115
                            else:
                                player_cheese -= 1
                                count += 1
                                print('Nothing happens.')
                        else:
                            print('Nothing happens. You are out of cheese!')
                        print(f"My gold: {player_gold}, My points: {player_point}")
                        print()
                    elif horn == 'stop hunt':
                        break
                    else:
                        print('Do nothing.')

                    if count == 5:
                        answer = input('Do you want to continue to hunt? ')
                        if answer == 'yes':
                            continue
                        elif answer == 'no':
                            print()
                            break
            elif select == 3:
                gold, cheese = shop.main(player_gold, player_cheese, player_trap)
                player_gold = gold
                player_cheese = cheese
                continue

            else:
                pass

    if tutorial == 'skip':
        while True:
            print(f'''What do ye want to do now, Hunter {player_name}?
1. Exit game
2. Join the Hunt
3. The Cheese Shop''')
            select = input()
            select = int(select)

            if select == 1:
                break
            elif select == 2:
                count = 0
                while True:
                    print('Sound the horn to call for the mouse...')
                    horn = input('Sound the horn by typing "yes": ')
                    if horn == 'yes':
                        if player_cheese > 0:
                            if random.random() < 0.5:
                                count = 0
                                player_cheese -= 1
                                print('Caught a Brown mouse!')
                                player_gold += 125
                                player_point += 115
                            else:
                                player_cheese -= 1
                                count += 1
                                print('Nothing happens.')
                        else:
                            print('Nothing happens. You are out of cheese!')
                        print(f"My gold: {player_gold}, My points: {player_point}")
                        print()
                    elif horn == 'stop hunt':
                        break
                    else:
                        print('Do nothing.')
                    if count == 5:
                        answer = input('Do you want to continue to hunt? ')
                        if answer == 'yes':
                            continue
                        elif answer == 'no':
                            print()
                            break

            elif select == 3:
                gold, cheese = shop.main(player_gold, player_cheese, player_trap)
                player_gold = gold
                player_cheese = cheese
                print()
                continue


            else:
                pass


if __name__ == '__main__':
    main()
