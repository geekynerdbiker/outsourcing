from datetime import timedelta, datetime

# Problem 1
def calender1(start, end):
    ct = datetime(start, 1, 1)
    res = 0
    while ct.year <= end:
        res += (1 if ct.weekday() == 6 else 0)
        ct += timedelta(days=1)

    return res

# Problem 1
def calender2():
    # start = {1: Mon, 2: Tue, ... , 0: Sun}
    year, days, total, start = 1900, 365, 0, 1

    while year <= 2000:
        if year % 4 == 0:
            if year % 400 == 0:
                days = 365
            else:
                days = 366
        else:
            days = 365

        if year != 1900:
            total += (days + start) // 7
        start = (days + start) % 7
        year += 1

    return total


print(calender1(1901, 2000))
print(calender2())


# Problem 2
class Transformer(object):
    decimal_digits = '0123456789'

    def __init__(self, digits):
        self.digits = digits

    def from_decimal(self, i):
        return self._convert(i, self.decimal_digits, self.digits)

    def to_decimal(self, s):
        return int(self._convert(s, self.digits, self.decimal_digits))

    def _convert(self, number, fromdigits, todigits):
        if type(number) == str:
            rst, i, v, l = 0, 0, len(fromdigits), len(number)
            while i < l:
                index = fromdigits.lower().find(number[i].lower())
                rst += index * pow(v, l - i - 1)
                i += 1

            return rst

        elif type(number) == int:
            rst, l = '', len(todigits)
            while number > 0:
                rst = rst + str(todigits[number % l].lower())
                number = number // l

            return rst[::-1]
        raise NotImplementedError
