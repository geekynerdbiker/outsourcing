def square(block, x, y, z, l, w, h):
    blocks.fill(block, pos(x, y, z), pos(l + x, h + y, w + z))


def lower(x, altitude, z):
    # bottom
    square(5, x, altitude, z, 17, 17, 0)

    square(5, x - 1, altitude, z, 0, 0, 0)
    square(5, x, altitude, z - 1, 0, 0, 0)
    square(5, x - 1, altitude, z, 0, 0, 0)
    square(5, x, altitude, z + 17, 0, 0, 0)
    square(5, x + 17, altitude, z, 0, 0, 0)
    square(5, x + 16, altitude, z - 1, 0, 0, 0)
    square(5, x + 17, altitude, z + 16, 0, 0, 0)
    square(5, x + 16, altitude, z + 17, 0, 0, 0)

    # inner
    square(5, x + 2, altitude, z + 2, 13, 13, 12)

    # pillar
    square(5, x, altitude + 1, z, 2, 2, 10)
    square(5, x, altitude + 1, z + 15, 2, 2, 10)
    square(5, x + 15, altitude + 1, z, 2, 2, 10)
    square(5, x + 15, altitude + 1, z + 15, 2, 2, 10)

    for i in range(x, x + 16, 4):
        for j in range(x, x + 16, 4):
            if i == x and j == x:
                continue
            square(17, i, altitude + 1, j, 1, 1, 10)

    # pillar2
    square(5, x - 1, altitude + 1, z, 0, 0, 10)
    square(5, x, altitude + 1, z - 1, 0, 0, 10)

    square(5, x - 1, altitude + 1, z, 0, 0, 10)
    square(5, x, altitude + 1, z + 17, 0, 0, 10)

    square(5, x + 16, altitude + 1, z - 1, 0, 0, 10)
    square(5, x + 17, altitude + 1, z, 0, 0, 10)

    square(5, x + 16, altitude + 1, z + 17, 0, 0, 10)
    square(5, x + 17, altitude + 1, z + 16, 0, 0, 10)

    # roof
    square(5, x, altitude + 12, z, 17, 17, 0)

    square(5, x - 1, altitude + 12, z, 0, 0, 0)
    square(5, x, altitude + 12, z - 1, 0, 0, 0)
    square(5, x - 1, altitude + 12, z, 0, 0, 0)
    square(5, x, altitude + 12, z + 17, 0, 0, 0)
    square(5, x + 17, altitude + 12, z, 0, 0, 0)
    square(5, x + 16, altitude + 12, z - 1, 0, 0, 0)
    square(5, x + 17, altitude + 12, z + 16, 0, 0, 0)
    square(5, x + 16, altitude + 12, z + 17, 0, 0, 0)


def upper(x, altitude, z):
    # bottom & inner
    square(5, x, altitude, z, 17, 17, 1)
    square(5, x + 2, altitude, z + 2, 13, 13, 12)

    # pillar
    square(5, x, altitude + 2, z, 0, 0, 10)
    square(5, x, altitude + 2, z + 17, 0, 0, 10)
    square(5, x + 17, altitude + 2, z, 0, 0, 10)
    square(5, x + 17, altitude + 2, z + 17, 0, 0, 10)

    for i in range(x + 1, x + 18, 2):
        for j in range(x + 1, x + 18, 2):
            square(17, i, altitude + 2, j, 0, 0, 10)

    # pillar2
    square(5, x + 1, altitude + 2, z + 1, 0, 0, 10)
    square(5, x + 1, altitude + 2, z + 16, 0, 0, 10)
    square(5, x + 16, altitude + 2, z + 1, 0, 0, 10)
    square(5, x + 16, altitude + 2, z + 16, 0, 0, 10)

    # roof
    square(5, x, altitude + 12, z, 17, 17, 0)


def clock(x, altitude, z):
    # base
    square(5, x, altitude, z, 17, 17, 14)

    # outer pillar
    for i in range(x, x + 18):
        for j in range(x, x + 18):
            if i < x + 3 and j < x + 3:
                continue
            elif i > x + 16 and j > x + 16:
                continue
            elif i < x + 3 and j > x + 16:
                continue
            elif i > x + 16 and j < x + 3:
                continue

            # clock plate
            if i == x + 3 or i == x + 14 or j == x + 3 or j == x + 14:
                square(5, i - 1, altitude, j - 1, 0, 0, 14)
                square(5, i + 1, altitude, j + 1, 0, 0, 14)

                square(3, i - 1, altitude + 3, j - 1, 0, 0, 8)
                square(3, i + 1, altitude + 3, j + 1, 0, 0, 8)
            elif i == x + 4 or i == x + 13 or j == x + 4 or j == x + 13:
                if i % 2 == 0 and j % 2 == 0:
                    square(5, i - 1, altitude, j - 1, 0, 0, 14)
                    square(5, i + 1, altitude, j + 1, 0, 0, 14)

                square(3, i - 1, altitude + 3, j - 1, 0, 0, 2)
                square(3, i + 1, altitude + 3, j + 1, 0, 0, 2)
                square(35, i - 1, altitude + 6, j - 1, 0, 0, 2)
                square(35, i + 1, altitude + 6, j + 1, 0, 0, 2)
                square(3, i - 1, altitude + 9, j - 1, 0, 0, 2)
                square(3, i + 1, altitude + 9, j + 1, 0, 0, 2)
            elif i == x + 5 or i == x + 12 or j == x + 5 or j == x + 12:
                if i % 2 == 0 and j % 2 == 0:
                    square(5, i - 1, altitude, j - 1, 0, 0, 14)
                    square(5, i + 1, altitude, j + 1, 0, 0, 14)

                square(3, i - 1, altitude + 3, j - 1, 0, 0, 1)
                square(3, i + 1, altitude + 3, j + 1, 0, 0, 1)
                square(35, i - 1, altitude + 5, j - 1, 0, 0, 4)
                square(35, i + 1, altitude + 5, j + 1, 0, 0, 4)
                square(3, i - 1, altitude + 10, j - 1, 0, 0, 1)
                square(3, i + 1, altitude + 10, j + 1, 0, 0, 1)
            elif x + 6 <= i <= x + 11 or x + 6 <= j <= x + 11:
                if i % 2 == 0 and j % 2 == 0:
                    square(5, i - 1, altitude, j - 1, 0, 0, 14)
                    square(5, i + 1, altitude, j + 1, 0, 0, 14)

                square(3, i - 1, altitude + 3, j - 1, 0, 0, 0)
                square(3, i + 1, altitude + 3, j + 1, 0, 0, 0)
                square(35, i - 1, altitude + 4, j - 1, 0, 0, 6)
                square(35, i + 1, altitude + 4, j + 1, 0, 0, 6)
                square(3, i - 1, altitude + 11, j - 1, 0, 0, 0)
                square(3, i + 1, altitude + 11, j + 1, 0, 0, 0)
            else:
                continue

    # roof
    square(5, x, altitude + 14, z, 17, 17, 0)


def lower_roof(x, altitude, z):
    # bottom & inner
    square(5, x, altitude, z, 17, 17, 0)
    square(5, x + 5, altitude, z + 5, 10, 10, 5)

    # pillar
    square(5, x, altitude + 1, z, 0, 0, 4)
    square(5, x, altitude + 1, z + 17, 0, 0, 4)
    square(5, x + 17, altitude + 1, z, 0, 0, 4)
    square(5, x + 17, altitude + 1, z + 17, 0, 0, 4)

    for i in range(x + 1, x + 18, 2):
        for j in range(x + 1, x + 18, 2):
            square(17, i, altitude + 1, j, 0, 0, 4)

    # pyramid
    for i in range(5):
        square(22, x + i, altitude + 5 + i, z + i, 17 - i * 2, 17 - i * 2, 0)


def upper_roof(x, altitude, z):
    # bottom & inner
    square(5, x + 5, altitude, z + 5, 8, 8, 0)

    # pillar
    square(5, x + 5, altitude + 1, z + 5, 0, 0, 4)
    square(5, x + 5, altitude + 1, z + 13, 0, 0, 4)
    square(5, x + 13, altitude + 1, z + 5, 0, 0, 4)
    square(5, x + 13, altitude + 1, z + 13, 0, 0, 4)

    for i in range(x + 5, x + 13, 2):
        for j in range(x + 5, x + 13, 2):
            square(17, i + 1, altitude + 1, j + 1, 0, 0, 4)

    # pyramid
    layer = 0
    for i in range(7):
        for j in range(1, 10):
            if i < j:
                break
            square(22, x + 4 + i, altitude + 6 + layer, z + 4 + i, 12 - i * 2, 12 - i * 2, 0)
            layer += 1


def build():
    lower(2, 0, 2)
    lower(2, 13, 2)
    upper(2, 26, 2)
    upper(2, 39, 2)
    upper(2, 52, 2)
    clock(2, 65, 2)
    lower_roof(2, 80, 2)
    upper_roof(2, 90, 2)


build()
player.teleport(pos(-50, 0, -50))
