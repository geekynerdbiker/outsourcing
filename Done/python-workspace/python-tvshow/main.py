import re
import os.path

show = {}
rating = {}


def read_file(filename):
    f = open(filename, 'r')
    lines = f.readlines()

    for line in lines:
        if not parse_file(line):
            print(f'Could not be parsed: {line}')
        else:
            info = parse_file(line)
            dictionary_file(info)
            rating_file(info)

    f.close()


def print_file():
    for t, value in show.items():
        print(t)
        print(len(t) * '=')
        print(f'Average rating: {sum(rating[t]) / len(rating[t]):.3f}')
        print('{0:>10}'.format('Season') + '{0:>10}'.format('Episode') + '{0:>10}'.format('Rating'))
        for s, e, r in value:
            print(f'{str(s).zfill(2):>10}{str(e).zfill(2):>10}{r:>10.2f}')
        print('\n')


def parse_file(line):
    line = line.strip().lower()
    p = re.compile(
        r'(the )?(a )?\s*(?P<t>[^-.]+?)\s*[-.]\s*((s(?P<s>\d+))?(((e(?P<e_start>\d+))(?:-e?(?P<e_end>\d+))?)?))?\s*,'
        r'\s*(?P<r>.+)')
    match = re.fullmatch(p, line)
    if match:
        t = match.group('t')
        if match.group('s'):
            s = int(match.group('s'))
        else:
            s = 1
        if match.group('e_start'):
            e_start = int(match.group('e_start'))
        else:
            e_start = 1
        if match.group('e_end'):
            e_end = int(match.group('e_end'))
        else:
            e_end = e_start
        r = float(match.group('r'))

        return t, s, e_start, e_end, r

    else:
        return False


def dictionary_file(info):
    t, s, e_start, e_end, r = info
    if t not in show:
        show[t] = []

    for i in range(e_start, e_end + 1):
        show[t].append([s, i, r])


def rating_file(info):
    t, s, e_start, e_end, r = info
    if t not in rating:
        rating[t] = []

    for i in range(e_start, e_end + 1):
        rating[t].append(r)


name = input('Input filename: ')

if not name or not os.path.isfile(name):
    print('Invalid filename')
else:
    read_file(name)
    print_file()
