import turtle

t = turtle.Turtle()


def init_draw():
    t.reset()
    t.speed(10)
    t.ht()
    t.up()


def draw_filled_rectangle(loc_x, loc_y, height, width, color):
    t.up()
    t.goto(loc_x, loc_y)
    t.down()
    t.color(color)
    t.begin_fill()
    for _ in range(2):
        t.fd(width)
        t.rt(90)
        t.fd(height)
        t.rt(90)
    t.end_fill()


def draw_rectangle(loc_x, loc_y, height, width, color):
    t.up()
    t.goto(loc_x, loc_y)
    t.down()
    t.color(color)
    for _ in range(2):
        t.fd(width)
        t.rt(90)
        t.fd(height)
        t.rt(90)


def draw_moon(loc_x, loc_y, color, bgcolor, size, bg_size, bgdist, angle):
    t.up()
    t.goto(loc_x, loc_y)
    t.down()
    t.right(angle)
    t.color(color)
    t.begin_fill()
    t.circle(size)
    t.end_fill()
    t.up()
    t.goto(loc_x + bgdist, loc_y)
    t.down()
    t.color(bgcolor)
    t.begin_fill()
    t.circle(bg_size)
    t.end_fill()
    t.up()
    t.left(angle)


def draw_circle(loc_x, loc_y, size, color):
    t.up()
    t.goto(loc_x, loc_y)
    t.down()
    t.color(color)
    t.begin_fill()
    t.circle(size)
    t.end_fill()
    t.up()


def draw_five_star(size, loc_x, loc_y, color, angle):
    t.up()
    t.goto(loc_x, loc_y)
    t.right(angle)
    t.down()
    t.color(color)
    t.begin_fill()
    for side in range(5):
        t.fd(size)
        t.rt(145)
        t.fd(size)
        t.rt(72 - 145)
    t.end_fill()
    t.up()
    t.left(angle)


def draw_horizontal_line():
    t.begin_fill()
    t.forward(100)
    t.left(90)
    t.forward(12.5)
    t.left(90)
    t.forward(100)
    t.left(90)
    t.forward(12.5)
    t.end_fill()


def draw_vertical_line():
    t.begin_fill()
    t.forward(45)
    t.left(90)
    t.forward(12.5)
    t.left(90)
    t.forward(45)
    t.left(90)
    t.forward(12.5)
    t.end_fill()


def draw_space_1():
    t.left(180)
    t.penup()
    t.forward(18.75)
    t.pendown()
    t.right(90)


def draw_space_2():
    t.left(90)
    t.penup()
    t.forward(55)
    t.pendown()


def draw_space_3():
    t.right(90)
    t.penup()
    t.forward(55)
    t.pendown()
    t.left(180)


def draw_space_4():
    t.penup()
    t.forward(18.75)
    t.pendown()
    t.left(90)


def draw_circle_korea():
    t.penup()
    t.goto(-100, 0)
    t.pendown()

    t.color("red")
    t.begin_fill()
    t.right(90)
    t.circle(50, 180)
    t.circle(-50, 180)
    t.left(180)
    t.circle(100, 180)
    t.end_fill()

    t.color("blue")
    t.begin_fill()
    t.circle(50, 180)
    t.circle(-50, 180)
    t.circle(-100, 180)
    t.end_fill()


def draw_gun():
    t.color("black")
    t.penup()
    t.goto(-150, 75)
    t.pendown()
    t.right(45)
    draw_horizontal_line()
    draw_space_1()
    draw_horizontal_line()
    draw_space_1()
    draw_horizontal_line()


def draw_gon():
    t.penup()
    t.goto(100, -150)
    t.pendown()
    t.left(90)
    draw_vertical_line()
    draw_space_2()
    draw_vertical_line()
    draw_space_4()
    draw_vertical_line()
    draw_space_3()
    draw_vertical_line()
    draw_space_4()
    draw_vertical_line()
    draw_space_2()
    draw_vertical_line()


def draw_gam():
    t.penup()
    t.goto(160, 75)
    t.left(90)
    t.forward(12.5)
    t.pendown()
    t.left(90)
    draw_vertical_line()
    draw_space_2()
    draw_vertical_line()
    draw_space_4()
    t.penup()
    t.back(55)
    draw_horizontal_line()
    draw_space_4()
    draw_vertical_line()
    draw_space_2()
    draw_vertical_line()


def draw_lee():
    t.penup()
    t.goto(-180, -100)
    t.pendown()
    t.right(90)
    draw_horizontal_line()
    draw_space_1()
    draw_vertical_line()
    draw_space_2()
    draw_vertical_line()
    t.penup()
    t.left(180)
    t.forward(18.75)
    t.left(90)
    t.forward(55)
    t.left(180)
    t.pendown()
    draw_horizontal_line()


def draw_fill_rectangle(x, y, height, width, color):
    t.goto(x, y)
    t.pendown()
    t.color(color)
    t.begin_fill()
    t.forward(width)
    t.right(90)
    t.forward(height)
    t.right(90)
    t.forward(width)
    t.right(90)
    t.forward(height)
    t.right(90)
    t.end_fill()
    t.penup()


def draw_star(x, y, color, length):
    t.goto(x, y)
    t.setheading(0)
    t.pendown()
    t.begin_fill()
    t.color(color)
    for turn in range(0, 5):
        t.forward(length)
        t.right(144)
        t.forward(length)
        t.right(144)
    t.end_fill()
    t.penup()


def draw_stripes():
    x = -237
    y = 125

    for stripe in range(0, 6):
        for color in ["red", "white"]:
            draw_fill_rectangle(x, y, 250 / 13, 475, color)
            y = y - 250 / 13

    draw_fill_rectangle(x, y, 250 / 13, 475, 'red')


def draw_square():
    height = (7 / 13) * 250
    width = 0.76 * 250
    draw_fill_rectangle(-237, 125, height, width, 'navy')


def draw_six_stars_rows():
    start = 30
    lines = 250 / 13 + 6
    y = 112

    for row in range(0, 5):
        x = -222

        for star in range(0, 6):
            draw_star(x, y, 'white', 10)
            x = x + start
        y = y - lines


def draw_five_stars_rows():
    start = 30
    lines = 250 / 13 + 6
    y = 100

    for row in range(0, 4):
        x = -206

        for star in range(0, 5):
            draw_star(x, y, 'white', 10)
            x = x + start
        y = y - lines


def draw_cross(loc_x, loc_y, width, height, color, left_align, cross_width, cross_height):
    draw_filled_rectangle(((loc_x + ((cross_width - width) / 2)) - left_align), loc_y, cross_height, width, color)
    draw_filled_rectangle(loc_x, loc_y - ((cross_height - height) / 2), height, cross_width, color)


def draw_full_background(loc_x, loc_y, color):
    draw_filled_rectangle(loc_x, loc_y, 440, 750, color)


def draw_half_background(loc_x, loc_y, color):
    draw_filled_rectangle(loc_x, loc_y, 440 / 2, 750, color)


def draw_third_background(loc_x, loc_y, color):
    draw_filled_rectangle(loc_x, loc_y, 440 / 3, 750, color)


def draw_third_vert_background(loc_x, loc_y, color):
    draw_filled_rectangle(loc_x, loc_y, 440, 750 / 3, color)


def reset_draw():
    t.speed(10)
    draw_rectangle(-400, 200, 500, 800, 'white')
    t.up()
    t.goto(1000, 1000)


def draw_korea():
    print("Country Selected: Korea")
    init_draw()
    draw_circle_korea()
    draw_gun()
    draw_gon()
    draw_gam()
    draw_lee()


def draw_usa():
    print("Country Selected: USA")
    init_draw()
    draw_stripes()
    draw_square()
    draw_six_stars_rows()
    draw_five_stars_rows()
    t.hideturtle()


def draw_china():
    print("Country Selected: China")
    init_draw()
    draw_full_background(-375, 200, "red")
    draw_five_star(50, -240, 105, "yellow", 0)
    draw_five_star(15, -100, 50, "yellow", 0)
    draw_five_star(15, -95, 110, "yellow", 45)
    draw_five_star(15, -145, 160, "yellow", -45)
    draw_five_star(15, -145, 0, "yellow", -45)


def draw_japan():
    print("Country Selected: Japan")
    init_draw()
    draw_circle(0, -120, 100, "red")


def draw_vietnam():
    print("Country Selected: Vietnam")
    init_draw()
    draw_full_background(-375, 200, "red")
    draw_five_star(110, 10, 20, "yellow", 0)


def draw_singapore():
    print("Country Selected: Singapore")
    init_draw()
    draw_half_background(-375, 200, "red")
    draw_moon(-250, 20, "white", "red", 75, 75, 35, 0)
    star1x = -190
    star1y = 145
    draw_five_star(12, star1x, star1y, "white", 0)
    draw_five_star(12, star1x - 45, star1y - 35, "white", 0)
    draw_five_star(12, star1x + 43, star1y - 35, "white", 0)
    draw_five_star(12, star1x - 25, star1y - 85, "white", 0)
    draw_five_star(12, star1x + 25, star1y - 85, "white", 0)


def draw_france():
    print("Country Selected: France")
    init_draw()
    draw_third_vert_background(-375, 200, "blue")
    draw_third_vert_background(-125, 200, "white")
    draw_third_vert_background(125, 200, "red")


def draw_italy():
    print("Country Selected: Italy")
    init_draw()
    draw_third_vert_background(-375, 200, "green")
    draw_third_vert_background(-125, 200, "white")
    draw_third_vert_background(125, 200, "red")


def draw_austria():
    print("Country Selected: Austria")
    init_draw()
    draw_third_background(-375, 200, "red")
    draw_third_background(-375, 200 - (440 / 3), "white")
    draw_third_background(-375, 200 - (2 * (440 / 3)), "red")


def draw_germany():
    print("Country Selected: Germany")
    init_draw()
    draw_third_background(-375, 200, "black")
    draw_third_background(-375, 200 - (440 / 3), "red")
    draw_third_background(-375, 200 - (2 * (440 / 3)), "yellow")


if __name__ == "__main__":
    print("Country List: [Korea, USA, China, Japan, Singapore, Vietnam, France, Italy, Austria, Germany] or ALL")
    while True:
        selected = str(input("Country to draw: "))
        reset_draw()
        if selected.lower() == "korea":
            draw_korea()
            continue
        if selected.lower() == "usa":
            draw_usa()
            continue
        if selected.lower() == "china":
            draw_china()
            continue
        if selected.lower() == "japan":
            draw_japan()
            continue
        if selected.lower() == "vietnam":
            draw_vietnam()
            continue
        if selected.lower() == "singapore":
            draw_singapore()
            continue
        if selected.lower() == "france":
            draw_france()
            continue
        if selected.lower() == "italy":
            draw_italy()
            continue
        if selected.lower() == "austria":
            draw_austria()
            continue
        if selected.lower() == "germany":
            draw_germany()
            continue
        if selected.lower() == "all":
            draw_korea()
            reset_draw()
            draw_usa()
            reset_draw()
            draw_japan()
            reset_draw()
            draw_singapore()
            reset_draw()
            draw_france()
            reset_draw()
            draw_italy()
            reset_draw()
            draw_austria()
            reset_draw()
            draw_germany()
            reset_draw()
            continue
        else:
            print("Invalid Country\n")
            continue
