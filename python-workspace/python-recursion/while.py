# 일반적인 재귀# while 문
def test2(xs):
    rst = []
    while len(xs) > 0:
        rst.append([xs[0]])
        xs = xs[1:]

    return rst
