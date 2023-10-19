import turtle as t

def tree(length):
    if length > 5:
        t.forward(length)
        t.right(20)
        tree(length-15)
        t.left(40)
        tree(length - 15)
        t.right(20)
        t.backward(length)

t.speed(10)

t.left(90)
t.color("red")
tree(90)

t.left(120)
t.color("green")
tree(90)

t.left(120)
t.color("blue")
tree(90)
