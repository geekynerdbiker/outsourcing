# 참고자료 https://kosis.kr/statHtml/statHtml.do?orgId=101&tblId=DT_1IN1603
import turtle as t


def drawBar(height):
    t.begin_fill()
    t.left(90)
    t.forward(height)
    t.write(str(height), font=('Times New Roman', 16, 'bold'))
    t.right(90)
    t.forward(40)
    t.right(90)
    t.forward(height)
    t.left(90)
    t.end_fill()


men = [2782704, 3423638, 3719918, 4245158, 4071589, 2518527, 1369705, 413138, 34807]
women = [2562636, 3045966, 3547688, 4156244, 4035025, 2671383, 1785069, 866388, 123001]

for i in range(len(men)):
    men[i] *= 0.0001
    women[i] *= 0.0001

t.color("blue")
t.fillcolor("red")
t.pensize(3)

t.penup()
t.goto(-400, -400)
t.pendown()
for m in men:
    drawBar(m)

t.penup()
t.goto(100, -400)
t.pendown()
for w in women:
    drawBar(w)
