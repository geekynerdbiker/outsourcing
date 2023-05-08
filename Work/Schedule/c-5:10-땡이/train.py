Python 3.7.6 (tags/v3.7.6:43364a7ae0, Dec 19 2019, 00:42:30) [MSC v.1916 64 bit (AMD64)] on win32
Type "help", "copyright", "credits" or "license()" for more information.
>>> 
import sys

def intro():
    print("Larry: I'm Larry. I'll be your hunting instructor.")

def travel_to_camp():
    print("Larry: Let's go to the Meadow to begin your training!")
    enter = input('Press Enter to travel to the Meadow...')
    if enter == '\x1b':
        sys.exit()
    else:
        print('''Travelling to the Meadow...
Larry: This is your camp. Here you'll set up your mouse trap.''')

def setup_trap(trap: str) -> tuple:
    print("Larry: Let's get your first trap...")
    enter=input("Press Enter to view traps that Larry is holding...")
    if enter == '\x1b':
        sys.exit()
    else:    
        print('''Larry is holding...
Left: High Strain Steel Trap
Right: Hot Tub Trap''')
        trap_name=input('Select a trap by typing "left" or "right": ')
        trap_name = trap_name.strip().lower()

    if trap_name == '\x1b':
        sys.exit()

    elif trap_name == 'left':
        print('''Larry: Excellent choice.
Your "High Strain Steel Trap" is now set!''')
        trap = 'High Strain Steel Trap'

    elif trap_name == 'right':
        print('''Larry: Excellent choice.
Your "Hot Tub Trap" is now set!''')
        trap = 'Hot Tub Trap'
    
    else:
        print('''Invalid command! No trap selected.
Larry: Odds are slim with no trap!''')
        trap = 'Cardboard and Hook Trap'
    
    if trap_name == 'left' or trap_name == 'right':
        print('''Larry: You need cheese to attract a mouse.
Larry places one cheddar on the trap!''')
        return (trap, 1)
    else:
        return (trap, 0)

def sound_horn(horn: str) -> str:
    print("Sound the horn to call for the mouse...")
    horn_input=input('Sound the horn by typing "yes": ')
    horn_input=horn_input.strip().lower()
    if horn_input == '\x1b':
        sys.exit()
    else:    
        return horn_input

def basic_hunt(cheddar: int, horn_input: str) -> bool:
    if cheddar == 1 and horn_input == 'yes':
        print('''Caught a Brown mouse!
Congratulations. Ye have completed the training.''')
        return True
   
    elif (horn_input=='yes' and cheddar==0) or (horn_input!='yes' and cheddar==1):
        print('''Nothing happens.
To catch a mouse, you need both trap and cheese!''')
        return False

    else:
        print("Nothing happens.")
        return False
   

def end(hunt_status: bool):
    if hunt_status==True:
        print('Good luck~')
    pass


def main():
        intro()
        travel_to_camp()
        while True:
            setup=setup_trap('')
            horn_input=sound_horn('')
            hunt_status=basic_hunt(setup[1], horn_input)
            end(hunt_status)
        
            training=input('\nPress Enter to continue training and "no" to stop training: ')
            training=training.strip().lower()
            if training == 'no' or training == '\x1b':
                return setup
        
            else:
                continue

if __name__ == '__main__':
    main()     