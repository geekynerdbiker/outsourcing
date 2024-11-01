def solution():
    for k in range(9):
        line = ''
        for i in range(9 - k):
            line = line + '*'
        for i in range(k * 2):
            line = line + ' '
        for i in range((8 - k) * 2):
            line = line + '*'
        for i in range(k):
            line = line + ' '

        print(line + ' ********\n')

    for k in range(1, 10):
        line = ''
        for i in range(k):
            line = line + '*'
        for i in range((9-k) * 2):
            line = line + ' '
        for i in range(k * 2):
            line = line + '*'
        for i in range((9-k)):
            line = line + ' '

        print(line + ' ********\n')


solution()
