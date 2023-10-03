import sys


def validate_input(matrix):
    # To output the errors in the right order
    errors = {
        "rectangular": {
            "status": False,
            "message": "Error: Bludiste neni obdelnikove!"
        },
        "entry": {
            "status": False,
            "message": "Error: Vstup neni vlevo nahore!"
        },
        "exit": {
            "status": False,
            "message": "Error: Vystup neni vpravo dole!"
        },
        "width": {
            "status": False,
            "message": "Error: Sirka bludiste je mimo rozsah!"
        },
        "height": {
            "status": False,
            "message": "Error: Delka bludiste je mimo rozsah!"
        },
        "characters": {
            "status": False,
            "message": "Error: Bludiste obsahuje nezname znaky!"
        },
        "surrounding": {
            "status": False,
            "message": "Error: Bludiste neni oplocene!"
        }
    }

    # Check if the maze has the right width
    if not len(matrix[0]) in range(5, 100):
        errors["width"]["status"] = True

    # Check if the maze has the right height
    if not len(matrix) in range(5, 50):
        errors["height"]["status"] = True

    # Check if entry is in the top left corner
    if matrix[0][1] != ".":
        errors["entry"]["status"] = True

    # Check if exit is in the bottom right corner
    if matrix[len(matrix) - 1][len(matrix[0]) - 2] != ".":
        errors["exit"]["status"] = True

    for i, row in enumerate(matrix):
        if len(row) != len(matrix[0]):
            errors["rectangular"]["status"] = True
            break

        for j, char in enumerate(row):
            if i == 0:
                if j != 1 and char != "#":
                    errors["surrounding"]["status"] = True
            elif i == len(matrix) - 1:
                if j != len(row) - 2 and char != "#":
                    errors["surrounding"]["status"] = True
            else:
                if j == 0 or j == len(row) - 1:
                    if char != "#":
                        errors["surrounding"]["status"] = True
                else:
                    if char not in ".#":
                        errors["characters"]["status"] = True

    for key in errors:
        if errors[key]["status"]:
            sys.stderr.write(errors[key]["message"] + "\n\n")
            return False

    return True


def find_obligatory_paths(maze):
    # Find path functions
    changed_paths = []
    def find_path(x, y, maze):
        # check if out of bounds
        if maze[y][x] != ".":
            return None

        # Base case (found a way)
        if x == len(maze[0]) - 2 and y == len(maze) - 1:
            return [(x, y)]

        maze[y][x] = "!"
        changed_paths.append((x, y))

        for dx, dy in ((0, 1), (1, 0), (0, -1), (-1, 0)):
            path = find_path(x + dx, y + dy, maze)
            if path is not None:
                return [(x, y)] + path

        return None

    # generate density map to place barriers
    inserted_barriers = []
    for i, row in enumerate(maze):
        if i in (0, 1) or i in (len(maze) - 1, len(maze) - 1):
            continue
        for j, cell in enumerate(row):
            if j in (0, 1) or j in (len(row) - 1, len(row) - 2) or cell == "#":
                continue
            if cell == "." \
                    and maze[i - 1][j] == "." \
                    and maze[i + 1][j] == "." \
                    and maze[i + 1][j - 1] == "." \
                    and maze[i + 1][j + 1] == "." \
                    and maze[i - 1][j + 1] == "." \
                    and maze[i - 1][j - 1] == "." \
                    and maze[i][j - 1] == "." \
                    and maze[i][j + 1] == ".":
                inserted_barriers.append((j, i))
                maze[i][j] = "#"

    obligatory_paths = []
    base_path = find_path(1, 0, maze)

    # reset maze
    for point in changed_paths:
        maze[point[1]][point[0]] = "."

    changed_paths = []

    if base_path is not None:
        obligatory_paths.append(base_path[0])
        obligatory_paths.append(base_path[1])
        obligatory_paths.append(base_path[len(base_path) - 1])
        obligatory_paths.append(base_path[len(base_path) - 2])
        for i, point in enumerate(base_path):
            if i in (0, 1, len(base_path) - 1, len(base_path) - 2):
                continue

            maze[point[1]][point[0]] = "#"
            result = find_path(1, 0, maze)

            # reset maze
            for rest_point in changed_paths:
                maze[rest_point[1]][rest_point[0]] = "."

            changed_paths = []

            if result is None:
                obligatory_paths.append(point)

            maze[point[1]][point[0]] = "."

    # reset inserted barriers
    for point in inserted_barriers:
        maze[point[1]][point[0]] = "."

    return obligatory_paths


# Maze parsing
input_maze = []

while True:
    try:
        line = input()
        if line == '':
            break

        input_maze.append(list(line))
    except EOFError:
        break

# Maze validation
validation_result = validate_input(input_maze)

if validation_result:
    # Maze solving
    result = find_obligatory_paths(input_maze)

    if result is None:
        sys.exit(1)

    for point in result:
        input_maze[point[1]][point[0]] = "!"

    # Maze output
    for row in input_maze:
        print("".join(row))

else:
    sys.exit(1)
