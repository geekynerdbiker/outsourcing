def HEAPIFY(A, i, n):
    largest = i

    # 자식 노드 중 더 큰 값을 찾음 (왼쪽)
    if 2 * i + 1 < n and A[2 * i + 1] > A[i]:
        largest = 2 * i + 1

    # 자식 노드 중 더 큰 값을 찾음 (오른쪽)
    if 2 * i + 2 < n and A[2 * i + 2] > A[largest]:
        largest = 2 * i + 2

    # 찾은 자식의 값이 원래 있던 노드와 다르면 교환
    if largest != i:
        A[i], A[largest] = A[largest], A[i]
        HEAPIFY(A, largest, n)


def BUILD_HEAP(A, n):
    # 트리 구조를 힘 구조로의 변환을 위한 BUILD_HEAP 함수 호출
    for i in range(n // 2 - 1, -1, -1):
        HEAPIFY(A, i, n)


def HEAPSORT(A, n):
    BUILD_HEAP(A, n)
    # 힙 크기를 1씩 줄여가면서 반복적으로 힙 구성
    for i in range(n - 1, 0, -1):
        A[i], A[0] = A[0], A[i]
        HEAPIFY(A, 0, i)


if __name__ == '__main__':
    A = [12, 11, 13, 5, 6, 7]

    HEAPSORT(A, len(A))
    n = len(A)

    print("Sorted Aay is")
    for i in range(n):
        print("%d" % A[i], end=" ")
