#  -------------- 1. zap reading --------------
def iszapreadable(arr):
    if len(arr) == 1:
        return True

    if len(set(arr)) != len(arr):
        return False

    visited = [0 for _ in range(len(arr))]
    visited[0] = 1

    idx = 0
    while True:
        idx += arr[idx]
        idx %= len(arr)
        visited[idx] += 1
        if visited[idx] > 2:
            return False
        if visited.count(1) == len(arr):
            return True


def zapbook(n):
    if n == 1:
        return [1]
    if n % 2 == 1:
        return []

    idx, step = 0, 0
    arr = [0 for _ in range(n)]
    if n & (n - 1) == 0:
        while arr.count(0) != 0:
            arr[step] = idx + 1
            step += arr[step]
            idx += 1
            step %= n
        return arr
    else:
        return [n - 1 - i * 2 for i in range(n // 2)] + [n - i * 2 for i in range(n // 2)]


#  -------------- 2. Whereabouts --------------
def lucas_number(n):
    if n == 0:
        return 2

    if n == 1:
        return 1

    dp = [0 for i in range(n + 1)]
    dp[0] = 2
    dp[1] = 1

    for i in range(2, n + 1):
        dp[i] = dp[i - 1] + dp[i - 2]

    return dp[n]


def fragment(a, b, c):
    s = str(lucas_number(a))
    return int(s[b - 1:c])


def digits(s):
    rst = ''
    for d in s.upper():
        if 'A' <= d <= 'Z':
            rst += str(ord(d) - ord('A') + 1)
        elif '0' <= d <= '9':
            rst += d
    return rst


def whereabouts(s):
    number = digits(s)

    idx = 2
    dp = [2, 1]
    while str(dp[idx-1]).rfind(number) == -1:
        dp.append(dp[idx - 1] + dp[idx - 2])
        idx += 1

    lucas = dp[idx-1]
    pos = str(lucas).rfind(number)

    return '#' + str(idx) + ", " + str(pos + 1) + "-" + str(pos + len(number)) + " of " + str(len(str(lucas)))

#  -------------- 3. A reflective rainbow --------------
def letter_value(s):
    if not isinstance(s, str) and not isinstance(s, tuple) and not isinstance(s, list):
        raise AssertionError('invalid letters')
    if len(s) % 2 != 0:
        raise AssertionError('invalid letters')

    rst = {}
    idx = int(-1 * len(s) / 2)
    for c in s:
        if s.count(c.lower()) + s.count(c.upper()) > 1 or not c.isalpha():
            raise AssertionError('invalid letters')
        rst[c.upper()] = idx
        idx += 1
        if idx == 0:
            idx += 1

    return rst

def word_value(c, s):
    d = letter_value(s)

    rst = 0
    try:
        for w in c.upper():
            rst += d[w]
    except:
        raise AssertionError('invalid word')
    return rst


def rainbow(l, s):
    if not isinstance(l, list) and not isinstance(l, tuple):
        return False

    d = letter_value(s)
    idx = 0
    for w in l:
        if word_value(w, s) != idx:
            return False
        idx += 1
    return True


def reflected(l, s):
    d = letter_value(s)
    d2 = {}

    for w in l:
        d2[w] = word_value(w, s)

    d2 = dict(sorted(d2.items(), key=lambda x: (x[1], x[0].upper())))

    return tuple(d2.keys())

#  -------------- 4. Platypus --------------
from fractions import Fraction

def word_fraction(w, f):
    if len(w) % f.denominator != 0:
        raise AssertionError('invalid fraction')

    if len(w) != f.denominator:
        num = int(f.numerator * len(w) // f.denominator)
        den = int(f.denominator * len(w) // f.denominator)
    else:
        num = f.numerator
        den = f.denominator
    if f.numerator >= 0:
        return w[:num]
    else:
        return w[num:]


def combine(l, f):
    rst = ''
    for i in range(len(l)):
        rst += word_fraction(l[i], f[i])

    return rst


def decompose(s):
    s = s.replace('What is ', '').replace('and ', '').replace(',', '').replace('?', '')
    l = s.split(' ')

    w, f = [], []
    for i in range(len(l)):
        if i % 2 == 0:
            l2 = l[i].split('/')
            f.append(Fraction(int(l2[0]), int(l2[1])))
        else:
            w.append(l[i])

    return w, f


def answer(s):
    w, f = decompose(s)
    return combine(w, f)


#  -------------- 5. Readouts --------------
d = {0: [0, 1, 2, 4, 5, 6], 1: [1, 4], 2: [0, 2, 3, 4, 6], 3: [0, 2, 3, 5, 6], 4: [1, 2, 3, 5], 5: [0, 1, 3, 5, 6],
     6: [0, 1, 3, 4, 5, 6], 7: [0, 2, 5], 8: [0, 1, 2, 3, 4, 5, 6], 9: [0, 1, 2, 3, 5, 6]}


def digit2segments(n):
    if not isinstance(n, int):
        raise AssertionError('invalid digit')
    if n < 0 or n > 9:
        raise AssertionError('invalid digit')
    return set(d[n])


def segments2digit(s):
    if not isinstance(s, set):
        raise AssertionError('invalid segments')

    s = sorted(s)
    if not isinstance(s, set):
        s = list(s)

    for k, v in d.items():
        if v == s:
            return k
    raise AssertionError('invalid segments')


def next_readout(s):
    if not isinstance(s, str):
        raise AssertionError('invalid readout')
    for c in s:
        if not c.isdigit():
            raise AssertionError('invalid readout')
    segments = []
    for d in s:
        segments += digit2segments(int(d))

    rst = ''
    for i in range(7):
        rst += str(segments.count(i))

    return rst


def cycle(s):
    if not isinstance(s, str):
        raise AssertionError('invalid readout')

    rst = [s]
    next = ''
    while rst.count(next) < 2:
        if next == '':
            next = next_readout(s)
        else:
            next = next_readout(next)
        rst.append(next)

    return rst[:-1]

#  -------------- 6. Rövarspråket --------------
vowels = ['a', 'e', 'i', 'o', 'u']


def encode(s):
    rst = ''

    i = 0
    s2 = s.lower()
    while i < len(s):
        if s2[i] in vowels or s2[i] == ' ' or not s2[i].isalpha():
            if i == 0:
                rst += s[:i + 1]
                s = s[i + 1:]
                s2 = s2[i + 1:]
                i = 0
            else:
                rst += s[:i] + 'o' + s[:i].lower() + s[i]
                s = s[i + 1:]
                s2 = s2[i + 1:]
                i = 0
        else:
            i += 1

    if len(s) != 0:
        rst += s + 'o' + s
    return rst


def decode(s):
    rst = ''

    i = 0
    s2 = s.lower()
    while i * 2 < len(s2):
        if s2[i] in vowels or s2[i] == ' ' or not s2[i].isalpha():
            if i == 0:
                rst += s[:i + 1]
                s = s[i + 1:]
                s2 = s2[i + 1:]
                i = 0
                continue
            if s2[i] == 'o' and s2[:i] == s2[i + 1:i * 2 + 1]:
                rst += s[:i]
                s = s[i * 2 + 1:]
                s2 = s2[i * 2 + 1:]
                i = 0
        else:
            i += 1
    return rst