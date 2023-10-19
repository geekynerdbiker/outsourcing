# Do not import any module
# If any module is imported, It will be considered fail
def find_apple(field: list) -> int:
    # direction search
    dr = [0, 0, 1, -1]
    dc = [1, -1, 0, 0]
    # initialization
    ans = 987654321
    M = len(field)
    N = len(field[0])
    visited = [[-1 for _ in range(N)] for _ in range(M)]

    def __DFTHELP(r: int, c: int, step: int) -> None:
        # Complete __DFTHELP function for DFT recursion #
        if field[r][c] == '*':
            if visited[r][c] > step or visited[r][c] < 0:
                visited[r][c] = step
            return

        if visited[r][c] == -1:
            visited[r][c] = 0

        for x, y in zip(dr, dc):
            rx, cy = r + x, c + y
            if 0 <= rx < M and 0 <= cy < N:
                if visited[rx][cy] != 0 and field[rx][cy] != -1:
                    __DFTHELP(rx, cy, step + 1)
                    if visited[rx][cy] == 0:
                        visited[rx][cy] = -1

    def DFT():
        __DFTHELP(0, 0, 0)

    ans = DFT()
    for i in range(M):
        for j in range(N):
            if field[i][j] == '*':
                ans = visited[i][j]
    return ans


print(find_apple([[0, 0, 0, 0, 0],
                  [0, -1, -1, -1, -1],
                  [0, '*', -1, -1, 0],
                  [0, -1, 0, 0, 0],
                  [0, -1, -1, 0, -1],
                  [0, -1, 0, -1, -1]]))
print(find_apple([[0, 0, 0, 0, 0],
                  [-1, 0, 0, '*', 0],
                  [0, -1, 0, 0, -1],
                  [0, -1, 0, 0, 0],
                  [0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0]]))
print(find_apple([[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, -1, 0, 0, '*', 0],
                  [0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, -1],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, -1, -1, 0, -1, 0, 0, 0, 0, 0]]))
