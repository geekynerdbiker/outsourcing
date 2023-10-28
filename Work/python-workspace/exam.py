################################# 1

################################# 2
fin = "all_btl_data_head.csv"
with open(fin, 'r') as file:
    for line in file:
        for item in line.split(','):
            print(item)


################################# 3
from datetime import datetime


def time_stamp(line):
    dt_isoformat = datetime.strptime(line.split(' = ')[1], '%b %d %Y %H:%M:%S')
    dt_isoformat = dt_isoformat.strftime()
    return dt_isoformat


# a line in 'hi2011_t01.btl'

line = '* NMEA UTC (Time) = Sep 11 2020 09:56:57'

time_stamp(line)