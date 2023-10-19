"""
Prob 5
"""

answer = input("Do you have a Bachelor Degree? (y/n): ")
if answer == "y":
    answer = input("Have you passed the CPA exam? (y/n): ")
    if answer == "y":
        answer = input("Do you have one year of professional experience? (y/n): ")
        if answer == "y":
            print("Congratulations! You are qualified to obtain a CPA license!")
        else:
            print("Sorry, you also need one year of professional experience.")
    else:
        print("Sorry, you need to pass the CPA exam.")
else:
    print("Sorry, you need to have a Bachelor Degree first.")
