# 일반적인 재귀
def test(xs):
    if xs != []:
        if len(xs) == 1:
            return [[xs[0]]]
        return [[xs[0]]] + test(xs[1:])
    else:
        return
