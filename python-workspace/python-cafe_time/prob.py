capacity, customers = input().split(' ')

current = 0
visitor = 0

l = []
for i in range(int(customers)):
    inp = input().split(' ')
    l.append(inp)

l.sort()

curr = []
for i in range(int(customers)):
    if current < int(capacity):
        curr.append(l[i])
        curr.sort(key=lambda x: x[1])
        current += 1
        visitor += 1
    else:
        length = len(curr)
        for j in range(len(curr)):
            if l[i][0] < curr[j][1]:
                continue
            else:
                del curr[j]
                curr.append(l[i])
                visitor += 1
                break

print(visitor)

'''
input1)
2 4
10:00:30 23:59:59
09:30:22 17:50:30
09:30:10 21:39:15
22:10:00 23:02:13

output1)
3
'''

'''
input2)
3 5
00:00:00 23:59:59
10:00:30 23:59:59
09:30:22 09:50:30
21:30:10 21:39:15
16:10:00 17:02:13

output2)
5
'''
