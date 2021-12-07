import pickle
import random
import time

"""
    maze.py는 제출할 필요 없음. 수정하지도 말 것.
    오류 발견 시 제보 바람
    
    (height x width) 미로
    사방이 벽으로 둘러쌓임. 따라서 실제 리스트 크기는 (height + 2) x (width + 2)
    벽을 제외하면
      maze[1][1], maze[1][2], ... maze[1][width],
      maze[2][1], maze[2][2], ... maze[2][width],
      maze[height][1],        ... maze[height][width]
    까지 사용
    길찾기의 시작 위치는 (1, 1), 목적지는 (height, width)로 고정
"""

class Maze:
    view_delay_sec = 1.0

    def __init__(self, height, width, ratio=0.5):
        self.height = height
        self.width = width
        self.start_row, self.start_col = 1, 1
        self.end_row, self.end_col = height, width

        self._maze_init()
        self._fill(ratio)

    def _maze_init(self):
        hwall = ['#'] * (self.width + 2)
        self.maze = [hwall]
        for row in range(1, self.height + 1):
            self.maze.append(['#'] + [' '] * self.width + ['#'])
        self.maze.append(hwall)

    def _fill(self, ratio):
        empty_slots = []
        for row in range(1, self.height + 1):
            for col in range(1, self.width + 1):
                if (row, col) not in [(1, 1), (self.height, self.width)]:
                    empty_slots.append((row, col))

        n_blk = int(self.height * self.width * ratio)
        inner_walls = random.choices(empty_slots, k=n_blk)
        for row, col in inner_walls:
            self.maze[row][col] = '#'

    def in_range(self, row, col):
        return 0 <= row <= self.height and 0 <= col <= self.width

    def is_empty(self, row, col):
        return self.maze[row][col] == ' '

    def is_wall(self, row, col):
        return self.in_range(row, col) and self.maze[row][col] == '#'

    def save(self, filename):
        try:
            with open(filename, "wb") as f:
                pickle.dump(self, f)
            return True
        except IOError:
            return False

    @classmethod
    def load(cls, filename):
        try:
            with open(filename, "rb") as f:
                obj = pickle.load(f)
            return obj
        except IOError:
            return None

    def __repr__(self):
        repr = []
        for row in self.maze:
            repr.append(''.join(row))
        return '\n'.join(repr)

    def is_valid_path(self, path):
        def _neighbors(r1, c1, r2, c2):
            return (r1 - r2, c1 - c2) in [(1, 0), (0, 1), (-1, 0), (0, -1)]

        if len(path) < 1 or path[0] != (1, 1):
            return False

        for i in range(1, len(path)):
            if not self.is_empty(*path[i]):
                return False

            if not _neighbors(*path[i - 1], *path[i]):
                return False

        if path[-1] != (self.height, self.width):
            return False

        return True

    def view_path(self, path):
        if not self.is_valid_path(path):
            print("view_path(): Not a valid path")
            return

        print("view_path() starts from (1, 1)... ")
        print()
        time.sleep(Maze.view_delay_sec)

        cnt = 0
        for row, col in path:
            cnt += 1
            print('current =', (row, col), ', length =', cnt)
            self.maze[row][col] = '@'
            print(self)
            print()
            time.sleep(Maze.view_delay_sec)

        print("view_path() finished at ({}, {}), length = {}".format(self.height, self.width, len(path)))
        print()

        for row, col in path:
            self.maze[row][col] = ' '


# 어떤 식으로 만들어졌는지 보여주기 위한 코드
if __name__ == '__main__':
    # 미로 1개 생성. H x W
    # ratio는 (H x W) 안의 칸 중에서 벽 '#'의 비율
    HEIGHT, WIDTH, RATIO = 6, 8, 0.3
    maze = Maze(HEIGHT, WIDTH, RATIO)

    # 화면 출력
    print(maze)

    # 미로 1개를 파일로 저장
    save_result = maze.save("sample.maze")
    if not save_result:
        print("save() failed")
        exit(0)

    # 미로 1개를 파일에서 불러옮
    # classmethod 이므로 변수가 아니라 클래스 이름(Maze)으로 호출
    # 리턴값은 Maze 클래스의 인스턴스
    maze = Maze.load("sample.maze")
    if not maze:
        print("load() failed")
        exit(0)

    # (1, 1) 로 시작하지 않거나,
    # (HEIGHT, WIDTH) 로 끝나지 않거나,
    # 이동 방향이 상하좌우 네 방향이 아니거나
    # 벽'#'이 포함된 경로는 invalid
    path1 = [(1, 1), (3, 3)]
    path2 = [(1, 1), (2, 2), (3, 3), (4, 4), (5, 5)]
    print('path1 =', path1)
    print('path1 valid? =', maze.is_valid_path(path1))
    print()
    print('path2 =', path2)
    print('path2 valid? =', maze.is_valid_path(path2))

    # invalid path는 view_path()를 호출해도 그려서 보여주지 않음
    maze.view_path(path1)
    print()

    # 다른 예1
    HEIGHT, WIDTH, RATIO = 1, 1, 0.0
    maze = Maze(HEIGHT, WIDTH, RATIO)
    print(maze)
    path3 = [(1, 1)]
    print('path3 =', path3)
    print('path3 valid? =', maze.is_valid_path(path3))

    # 다른 예2
    HEIGHT, WIDTH, RATIO = 3, 3, 0.0
    maze = Maze(HEIGHT, WIDTH, RATIO)
    print(maze)
    path4 = [(1, 1), (1, 2), (1, 3), (2, 3), (3, 3)]
    print('path4 =', path4)
    print('path4 valid? =', maze.is_valid_path(path4))
    print()

    # path4 보여주기
    input('press enter to continue...')
    maze.view_path(path4)

