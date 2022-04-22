END = False
total_sales = 0
stock = {}
sold = {}
price_tag = {}


def read_stock():
    with open("data/input/grocery.txt", "r") as f:
        for line in f:
            item_type, count = line.split()
            stock[item_type] = int(count)
            sold[item_type] = 0
    f.close()


def read_price():
    with open("data/input/price.txt", "r") as f:
        for line in f:
            item_type, price = line.split()
            price_tag[item_type] = int(price)
    f.close()


def out_stock():
    with open("data/input/output.txt", "w") as f:
        for item in stock:
            f.write(item + ": " + str(stock[item]) + " left.\n")
        f.write("\nThe total sales of the convenience store is " + str(total_sales) + " Won.\n")
    f.close()


def sell():
    global total_sales
    print("Sales List:", end=' ')
    for item in stock:
        print(item, end=' ')
    print('\n')
    request = input("What would you like to buy? ")

    if request not in stock:
        print("You can only enter items in the list\n")
        return

    if stock[request] == 0:
        print("The item is out of stock\n")
        return

    while True:
        count = input("How many do you want to buy? ")
        if count.isdigit() and stock[request] >= int(count):
            break
        elif not count.isdigit():
            print("Tell us a number.")
        elif stock[request] < int(count):
            print("We only have " + str(stock[request]) + " " + request + ".")
    stock[request] -= int(count)
    sold[request] += int(count)

    money = price_tag[request] * int(count)
    total_sales += money
    print("The price is " + str(money) + " won.\nThank you for your purchase.\n")

    check()


def check():
    soldout = []

    for item in stock:
        if stock[item] == 0:
            soldout.append(item)

    for item in soldout:
        stock.__delitem__(item)

    for item in stock:
        print(item + ": " + str(stock[item]))


def sales():
    print("The total sales of the convenience store is " + str(total_sales) + " Won.\n")


def finish():
    out_stock()
    print("I'm done with my work!")
    global END
    END = True


def get_input():
    print("Enter number (1: sell things), (2: check stock), (3: check total sales), (4: finish)")
    inp = input()

    if inp == "1":
        sell()
    elif inp == "2":
        check()
    elif inp == "3":
        sales()
    elif inp == "4":
        finish()
    else:
        print("Wrong input.\n ")
        get_input()


def read_output():
    with open("data/input/output.txt", "r") as f:
        for line in f:
            print(line)
    f.close()


def main():
    read_stock()
    read_price()

    while END is False:
        get_input()

    read_output()


main()
