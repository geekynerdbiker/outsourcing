import utils
from queue import Queue
import collections
from collections import defaultdict
import heapq


class Solution(object):
    def leastStepQ1b(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """

        m, n = len(grid), len(grid[0])  # don't remove this line

        moves = [
            (1, 0),
            (-1, 0),
            (0, 1),
            (0, -1),
        ]

        # function to check it location is in the bound or not
        def inbound(i, j):
            return 0 <= i < m and 0 <= j < n

        # Creating Queue for BFS
        q = Queue(maxsize=10000)

        # visited set to keep track of visited cells
        visited = set()

        # initial state of robot = (0,0)
        # Assumption -- There is no wall at (0,0)
        # Robot has the capacity to destroy one wall (super power)

        # InitialState = (currPos, superPower, stepsTaken)
        initialState = ((0, 0), 1, 0)
        q.put(initialState)
        visited.add((initialState[0], initialState[1]))

        # While loop
        while not q.empty():
            currPos, super, steps = q.get()

            # if currPos reached, return steps
            if currPos == (m - 1, n - 1):
                return steps

            # move to adjacent cells
            for dx, dy in moves:
                x, y = currPos
                x, y = x + dx, y + dy
                if inbound(x, y) and ((x, y), super) not in visited:

                    # There's a wall
                    if grid[x][y] == 1:
                        if super:  # use super if available
                            q.put(((x, y), 0, steps + 1))
                            visited.add(((x, y), 0))
                    else:  # No wall
                        q.put(((x, y), super, steps + 1))
                        visited.add(((x, y), super))

        return -1  # no path available


if __name__ == '__main__':
    utils.A3_P1_1b_score()
