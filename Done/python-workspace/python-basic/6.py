"""
Prob 6
"""
import random
x = random.randint(1, 100)

while True:
    guess = int(input("Please guess a number between 1 to 100: "))

    if guess > x:
        print("Too big")
    elif guess < x:
        print("Too small")
    else:
        break

print("You win! The number is " + str(x))