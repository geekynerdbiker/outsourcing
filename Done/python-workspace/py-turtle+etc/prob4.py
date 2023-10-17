def calculate(time):
    total = 0

    if time >= 20:
        if time >= 30:
            total += (time - 30) * 1.5
            total += 30 * 1.3
        else:
            total += time * 1.3

    else:
        total = time

    return total

inp = int(input('Work Time? '))
min_wage = 9160

print(calculate(inp) * 9160)
