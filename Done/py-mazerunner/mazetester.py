from mazerunner import *
# from mazerunneropt import *

"""
    과제 제출물을 평가하기 위한 코드
    참고용이므로 제출할 필요 없음
    과제 평가 시에는 별도로 생성한 sample.maze 파일을 사용함
"""

# Maze.save()로 저장해 둔 미로 불러오기
# maze_sample = Maze.load("sample.maze")

# 랜덤 미로 생성하기
# maze_sample = Maze(height=3, width=3, ratio=0.0)
# maze_sample = Maze(height=5, width=5, ratio=0.0)
# maze_sample = Maze(height=5, width=5, ratio=0.2)
maze_sample = Maze(height=10, width=8, ratio=0.3)
print(maze_sample)
print()

# 경로 길이만 구했을 때 확인해볼 수 있는 코드
# path_len = shortest_path_length(maze_sample)
# print('shortest path length =', path_len)
# print()
# exit(0)

mypath = shortest_path(maze_sample)
print('mypath =', mypath)
print('length =', len(mypath))

if mypath:
    print('valid? =', maze_sample.is_valid_path(mypath))
    print()
    input('press enter to continue...')
    maze_sample.view_path(mypath)

# 이 아래는 채점을 위한 코드
# SCORE_MAX = 1000
# optimal_solution = shortest_path_opt(maze_sample)
#
# assert maze_sample.is_valid_path(mypath), "INVALID PATH"
# assert maze_sample.is_valid_path(optimal_solution), "INVALID OPTIMAL PATH"
#
# mylen, optlen = len(mypath), len(optimal_solution)
#
# mylen = min(mylen, optlen * 2)
# diff = mylen - optlen
# diff_ratio = diff / mylen
#
# myscore = SCORE_MAX * (1 - diff_ratio)
# print(myscore)
