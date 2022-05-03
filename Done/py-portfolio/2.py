import pulp

a = pulp.LpVariable('a', lowBound=0)
b = pulp.LpVariable('b', lowBound=0)
c = pulp.LpVariable('c', lowBound=0)

model = pulp.LpProblem(name='min', sense=pulp.LpMinimize)
model += 100 * a + 150 * b + 0 * c >= 70000
model += 80 * a + 120 * b + 0 * c >= 30000
model += 60 * a + 20 * b + 0 * c >= 30000
model += 10 * a + 0 * b + 0 * c >= 2000
model += a + b + c == 1000
model += 4000 * a + 5000 * b + 200 * c
model.solve()

print("최적 배합량")
print("재료 A: " + str(a.varValue))
print("재료 B: " + str(b.varValue))
print("재료 C: " + str(c.varValue))
print("최소 재료비: " + str(a.varValue * 4 + b.varValue * 5 + c.varValue * 0.2))

'''

2-1: 변수는 각각 재료 A, B, C로 선정.
     제약조건: (100a + 150b + 0c) >= 70000
             (80a + 120b + 0c) >= 30000
             (60a + 20b + 0c) >= 30000
             (10a + 0b + 0c) >= 2000
             a + b + c = 1000
             4000a = 5000b + 200c
'''