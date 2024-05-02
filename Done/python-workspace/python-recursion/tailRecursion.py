# 꼬리 재귀
def test1(xs):
    if type(xs[0]) == list:
        return xs

    xs.append([xs[0]])
    return test1(xs[1:])