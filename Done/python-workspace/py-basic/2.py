"""
Prob 2
"""

balls = [["red", "large"], ["blue", "small"], ["purple", "meidum"], ["blue", "large"], ["red", "small"],
         ["blue", "medium"]]

ct = 0

for ball in balls:
    if ball[1] == "small":
        if ball[0] == "red" or ball[0] == "purple":
            ct = ct + 1
print("The final count is: " + str(ct))
