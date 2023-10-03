from collections import deque
import sys


class Point:
    def __init__(self, prev, slope, length):
        self.prev = prev
        self.slope = slope
        self.length = length


def build_path(solution, point):
    path = []
    while point != None:
        path.append(point)
        point = solution[point[0]][point[1]].prev
    return path


# reindex - function that maps (x, y) to (x1, y1)
def find_paths_bfs(map, reindex, cmp):
    solution = [[Point((0, 0), -1, -1) for x in range(len(map[0]))] for y in range(len(map))]
    x0, y0 = reindex(0, 0)
    solution[x0][y0].slope = 0
    solution[x0][y0].prev = None
    queue = deque()
    queue.append((x0, y0))

    while queue:
        x, y = queue.popleft()
        for dx, dy in [(0, 1), (1, 0), (-1, 0), (0, -1)]:
            x1, y1 = x + dx, y + dy
            if 0 <= x1 < len(map) and 0 <= y1 < len(map[0]) and map[x1][y1] > map[x][y]:
                # 3 cases
                # 1) not visited
                # 2) better length
                # 3) same length and better slope
                if solution[x1][y1].slope == -1 \
                        or cmp(solution[x][y].length + 1, solution[x1][y1].length) \
                        or (solution[x1][y1].length == solution[x][y].length + 1
                            and cmp(solution[x1][y1].slope, max(solution[x][y].slope, map[x1][y1] - map[x][y]))):
                    solution[x1][y1].slope = max(solution[x][y].slope, map[x1][y1] - map[x][y])
                    solution[x1][y1].length = solution[x][y].length + 1
                    solution[x1][y1].prev = (x, y)
                    queue.append((x1, y1))
    return solution


def find_two_way_path(map, cmp):
    upsolution = find_paths_bfs(map, lambda x, y: (x, y), cmp)
    downsolution = find_paths_bfs(map, lambda x, y: (len(map) - 1 - x, len(map[0]) - 1 - y), cmp)
    max_height = None
    max_slope = None
    max_point = None
    for i in range(len(map)):
        for j in range(len(map[0])):
            if upsolution[i][j].slope != -1 and downsolution[i][j].slope != -1:
                slope = max(upsolution[i][j].slope, downsolution[i][j].slope)
                if max_slope is None or map[i][j] > max_height or (map[i][j] == max_height and cmp(max_slope, slope)):
                    max_slope = slope
                    max_height = map[i][j]
                    max_point = (i, j)

    path_up = build_path(upsolution, max_point)
    path_down = build_path(downsolution, max_point)

    path = path_up[1:][::-1] + path_down
    return path


try:
    size = input().split()
    rows = int(size[0])
    cols = int(size[1])
except IndexError:
    print("Error: Chybny vstup!", file=sys.stderr)
    sys.exit(1)
except ValueError:
    print("Error: Chybny vstup!", file=sys.stderr)
    sys.exit(1)

matrix = []
for _ in range(rows):
    try:
        row = list(map(int, input().split()))
        if len(row) != cols:
            print("Error: Chybny vstup!", file=sys.stderr)
            sys.exit(1)
        matrix.append(row)
    except ValueError:
        print("Error: Chybny vstup!", file=sys.stderr)
        sys.exit(1)

if len(matrix) != rows:
    print("Error: Chybny vstup!", file=sys.stderr)
    sys.exit(1)


def print_path(path):
    print(len(path))
    for x, y in path:
        print(matrix[x][y], end=" ")
    print()


if len(sys.argv) != 2:
    print_path(find_two_way_path(matrix, lambda x, y: x < y))
    print_path(find_two_way_path(matrix, lambda x, y: x > y))
else:
    argument = sys.argv[1]
    path = None
    if argument == "lift":
        print_path(find_two_way_path(matrix, lambda x, y: x < y))
    elif argument == "piste":
        print_path(find_two_way_path(matrix, lambda x, y: x > y))
    else:
        print(f"Chyba: Špatná hodnota argumentu '{argument}'.", file=sys.stderr)
        sys.exit(1)

sys.exit(0)
