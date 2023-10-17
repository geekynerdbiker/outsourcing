def min_plist_rec(xs):
    h, tail = xs  # 빈 리스트가 아니라고 가정하므로 항상 h와 tail로 잘라낼 수 있음
    if tail != ():
        if h < min_plist_rec(tail):
            return h
        else:
            return min_plist_rec(tail)
    else:  # tail == ()
        return h


def remove_plist_rec(v, xs):  # v라는 값의 원소 하나를 xs에서 제거
    if xs != ():
        h, tail = xs
        if h == v:
            return tail
        else:
            return h, (remove_plist_rec(v, tail))
    else:
        return xs


def selsort_rec(xs):
    if xs != ():
        h, tail = xs
        smallest = min_plist_rec(xs)
        tail = remove_plist_rec(smallest, xs)
        return smallest, selsort_rec(tail)
    else:
        return xs


print(selsort_rec((2, (1, ()))))
print(selsort_rec((3, (2, (1, ())))))
