from maze import Maze
from collections import deque

"""
    [과제 3]
        mazerunner.py 파일의 shortest_path() 함수를 완성하시오.
        이 파일 안에서 함수를 더 만들어도 괜찮지만, 주어진 함수의 매개변수는 건드리지 말 것
        maze.py, mazetester.py는 건드리지 말 것
    
    [올바른 경로valid path란?]
        (1, 1) 로 시작하지 않거나,
        (HEIGHT, WIDTH) 로 끝나지 않거나,
        이동 방향이 상하좌우 네 방향이 아니거나
        벽'#'이 포함된 경로는 유효하지 않은 경로 invalid path
        
    [경로 길이]
        편의상 "경로에 포함된 좌표 개수"로 정의함
        
    [제출]
        mazerunner.py
        
    [채점기준]
        invalid path이면 0점
        경로 길이가 최적해의 100%면 만점, (100+x)% 이면 점수는 (100-x)%
        즉, 경로 길이가 최적해의 두 배 이상이면 0점
        
        **웹에서 검색한 결과를 참고해서 작성한 경우 출처를 적어 둘 것
        평가에는 반영되지 않으나, 출처 표기 없이 유사한 코드가 발견되면 0점
"""


# 이 함수를 먼저 만들어보는 걸 추천함
# def shortest_path_length(maze):
# maze에서 (1, 1)에서 (maze.height, maze.width)까지 가는 최단 경로의 "길이"를 리턴(정수)
# 이동 방향은 상/하/좌/우 네 방향 (대각선x)
# 갈 수 있는 경로가 없으면 -1을 리턴한다.
# return -1


def shortest_path(maze):
    # maze에서 (1, 1)에서 (maze.height, maze.width)까지 가는 "최단 경로"를 리턴
    # 이동 방향은 상/하/좌/우 네 방향 (대각선x)
    # 경로는 2-tuple의 리스트로 만든다(예: [(1,1), (1, 2), (2, 2), ...]
    # 갈 수 있는 경로가 없으면 []를 리턴한다.
    height = maze.height
    width = maze.width

    dir = [[1, 0], [-1, 0], [0, 1], [0, -1]]
    visited = [[0] * (width + 2) for _ in range(height + 2)]
    route = [[0] * (width + 2) for _ in range(height + 2)]
    x, y = 1, 1

    path = deque()

    visited[x][y] = 1
    path.append((x, y))

    for i in range(0, height+2):
        for j in range(0, width+2):
            if maze.maze[i][j] != '#':
                visited[i][j] = 1

    while len(path):
        x, y = path.popleft()
        if x == height and y == width:
            break
        for d in range(4):
            next_x, next_y = x + dir[d][0], y + dir[d][1]
            if next_x == 1 and next_y ==1:
                continue
            if next_x < 1 or next_y < 1 or next_x >= height+1 or next_y >= width+1:
                continue
            if maze.is_wall(next_x, next_y):
                continue
            if visited[next_x][next_y] == 1:
                visited[next_x][next_y] = visited[x][y] + 1
                path.append((next_x, next_y))
                route[next_x][next_y] = (x, y);


    rst = [(height,width)]
    curr_x, curr_y = height, width
    while curr_x != 1 or curr_y != 1:
        rst.append(route[curr_x][curr_y])
        new_x, new_y = route[curr_x][curr_y]
        curr_x, curr_y = new_x, new_y

    rst.reverse()
    if rst[-1] != (height, width):
        return []
    return rst

