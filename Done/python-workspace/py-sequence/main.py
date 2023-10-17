def calculate(digit):
    tolerance = 1 / pow(10, digit)
    sequence = 1 / pow(10, digit)

    result = []
    while True:
        if tolerance > (72.62 - 60.12) / 95:
            break
        # print('tol:', tolerance)
        # print('seq:', sequence)

        temp_tol = tolerance
        sigma = 63.54 * 95

        l = [60.12]
        fn, fn1 = 60.12, 60.12

        for i in range(2, 95):
            fn = fn1
            fn1 = fn + temp_tol
            l.append(round(fn1, digit))
            temp_tol += sequence

        l.append(72.62)
        differ = sigma - sum(l)

        if differ < 0:
            tolerance += 1 / pow(10, digit)
            sequence = 1 / pow(10, digit)
            continue

        d = differ * 2 / (94 * 93)
        fd = d
        for i in range(len(l) - 1):
            if l[i] == 60.12:
                continue
            else:
                l[i] = round(l[i] + fd, digit)
                fd += d

        if sigma - sum(l) > 0.0001:
            break
        if l[94] - l[93] <= l[93] - l[92]:
            break

        re = list(reversed(l))
        if re not in result:
            print(re)
            result.append(re)

        sequence += 1 / pow(10, digit)


calculate(5)
