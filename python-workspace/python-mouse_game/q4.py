def intro():
    print("Larry: I'm Larry. I'll be your hunting instructor.")


def travel_to_camp():
    print("Larry: Let's go to the Meadow to begin your training!")
    enter = input('Press Enter to travel to the Meadow...')
    print('''Travelling to the Meadow...
Larry: This is your camp. Here you'll set up your mouse trap.''')


def setup_trap(trap: str) -> tuple:
    print("Larry: Let's get your first trap...")
    enter = input("Press Enter to view traps that Larry is holding...")
    print('''Larry is holding...
Left: High Strain Steel Trap
Right: Hot Tub Trap''')
    select_trap = input('Select a trap by typing "left" or "right": ')
    select_trap = select_trap.strip()

    if select_trap != 'left' and select_trap != 'right':
        print('''Invalid command! No trap selected.
Larry: Odds are slim with no trap!''')
        trap = 'Cardboard and Hook Trap'

    elif select_trap == 'left':
        print('''Larry: Excellent choice.
Your "High Strain Steel Trap" is now set!''')
        trap = 'High Strain Steel Trap'

    elif select_trap == 'right':
        print('''Larry: Excellent choice.
Your "Hot Tub Trap" is now set!''')
        trap = 'Hot Tub Trap'

    if select_trap == 'left' or select_trap == 'right':
        print('''Larry: You need cheese to attract a mouse.
Larry places one cheddar on the trap!''')
        return (trap, 1)
    else:
        return (trap, 0)


def sound_horn(horn: str) -> str:
    print("Sound the horn to call for the mouse...")
    horn_input = input('Sound the horn by typing "yes": ')
    return horn_input


def basic_hunt(cheddar: int, horn_input: str) -> bool:
    if cheddar == 1 and horn_input == 'yes':
        print('''Caught a Brown mouse!
Congratulations. Ye have completed the training.''')
        return True

    elif (horn_input == 'yes' and cheddar == 0) or (horn_input != 'yes' and cheddar == 1):
        print('''Nothing happens.
To catch a mouse, you need both trap and cheese!''')
        return False

    else:
        print("Nothing happens.")
        return False


def end(hunt_status: bool):
    if hunt_status == True:
        print('Good luck~')
    pass


def main():
    intro()
    travel_to_camp()
    setup = setup_trap('')
    horn_input = sound_horn('')
    hunt_status = basic_hunt(setup[1], horn_input)
    end(hunt_status)


if __name__ == '__main__':
    main()
