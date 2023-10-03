import sys

# codes = {
#     'a': 1,
#     'b': 2,
#     'c': 3,
#     'd': 4,
#     'e': 5,
#     'f': 6,
#     'g': 7,
#     'h': 8,
#     'i': 9,
#     'j': 10,
#     'k': 11,
#     'l': 12,
#     'm': 13,
#     'n': 14,
#     'o': 15,
#     'p': 16,
#     'q': 17,
#     'r': 18,
#     's': 19,
#     't': 20,
#     'u': 21,
#     'v': 22,
#     'w': 23,
#     'x': 24,
#     'y': 25,
#     'z': 26,
#     ' ': 31
# }


# Hash Function
def hash(s, m):
    sum = 0
    for i, value in enumerate(s):
        code = ord(value) - 96 if ord(value) != 32 else 31
        sum = sum + code * (32 ** i)

    return sum % m


# Node
class Node:
    def __init__(self, value):
        self.value = value
        self.quantity = 1


# Hash Table
class HashTable:
    def __init__(self, m=11):
        self.quantity = 0
        self.default_size = m
        self.table = [None] * m

    def __get_load_factor(self):
        return self.quantity / len(self.table)

    def __resize(self, size):
        self.quantity = 0
        old_table = self.table
        self.table = [None] * size

        for node in old_table:
            if node is None or node.value is None:
                continue

            index = self.insert(node.value)
            self.table[index].quantity = node.quantity

    def insert(self, value):
        calculated_hash = hash(value, len(self.table))

        next_node = self.table[calculated_hash]
        next_index = calculated_hash
        count = len(self.table)
        inserted_index = -1

        while count > 0:
            if next_node is None:
                self.table[next_index] = Node(value)
                self.quantity += 1
                inserted_index = next_index
                break

            if next_node.value is None:
                index = self.search(value)

                if index != -1:
                    self.table[index].quantity += 1
                    inserted_index = index
                    break
                else:
                    self.table[next_index] = Node(value)
                    self.quantity += 1
                    inserted_index = next_index
                    break

            if next_node.value == value:
                next_node.quantity += 1
                inserted_index = next_index
                break

            next_index = (next_index + 1) % len(self.table)
            next_node = self.table[next_index]
            count -= 1

        # Resize the table if the load factor is greater than 0.7
        if self.__get_load_factor() >= 0.7:
            self.__resize(len(self.table) * 2)
            return self.search(value)

        return inserted_index

    def search(self, value):
        calculated_hash = hash(value, len(self.table))

        next_node = self.table[calculated_hash]
        next_index = calculated_hash
        count = len(self.table)

        while count > 0:
            if next_node is None:
                return -1

            if next_node.value == value:
                return next_index

            next_index = (next_index + 1) % len(self.table)
            next_node = self.table[next_index]
            count -= 1

        return -1

    def delete(self, value):
        index = self.search(value)

        if index == -1:
            return -1

        self.table[index].quantity -= 1
        if self.table[index].quantity == 0:
            self.quantity -= 1
            self.table[index].value = None

        # Resize the table if the load factor is less than 0.3
        if self.__get_load_factor() <= 0.3:
            new_size = len(self.table) // 2
            if new_size >= self.default_size:
                self.__resize(new_size)

            return self.search(value)

        return index


class CommandManager:
    current_command = None
    current_person = None
    was_initialized = False
    hash_tables = {}
    names = {
        1: "Mirek",
        2: "Jarka",
        3: "Jindra",
        4: "Rychlonozka",
        5: "Cervenacek"
    }

    def __init_tables(self):
        if self.was_initialized:
            return

        for i in range(1, 6):
            self.hash_tables[i] = HashTable()

        self.was_initialized = True

    def __command_i(self, array):
        if self.was_initialized:
            return

        for i in range(0, len(array)):
            self.hash_tables[i + 1] = HashTable(int(array[i]))

        for j in range(len(array) + 1, 6):
            self.hash_tables[j] = HashTable()

        self.was_initialized = True

    def __command_a(self):
        self.current_command = 'a'
        self.current_person = None

    def __command_c(self, cis):
        if cis not in range(1, 6):
            sys.stderr.write("Error: Chybny vstup!\n")
            return

        self.current_command = 'c'
        self.current_person = cis

    def __command_p(self):
        if self.current_person is None:
            sys.stderr.write("Error: Chybny vstup!\n")
            return

        self.current_command = 'p'

        sys.stdout.write(self.names[self.current_person] + "\n")
        sys.stdout.write("\t"
                         + str(len(self.hash_tables[self.current_person].table))
                         + " "
                         + str(self.hash_tables[self.current_person].quantity)
                         + "\n")

    def __command_d(self):
        if self.current_person is None:
            sys.stderr.write("Error: Chybny vstup!\n")
            return

        self.current_command = 'd'

    def start(self):
        # Input parsing
        while True:
            try:
                line = input().strip()

                if line == '':
                    break

                # Initialization
                if not self.was_initialized:
                    if len(line) >= 2 and line[0] == '#' and line[1] == 'i':
                        args = line.split(' ')

                        if args[0] != '#i':
                            sys.stderr.write("Error: Chybny vstup!\n")
                            continue

                        self.__command_i(args[1::])
                        continue
                    else:
                        self.__init_tables()

                # Command parsing and validation
                if line[0] == '#':
                    args = line.split(' ')

                    if len(args[0]) != 2:
                        sys.stderr.write("Error: Chybny vstup!\n")
                        continue

                    command = line[1]
                    if command == 'a':
                        self.__command_a()
                        continue
                    elif command == 'p':
                        self.__command_p()
                        continue
                    elif command == 'd':
                        self.__command_d()
                        continue
                    elif command.isdigit():
                        self.__command_c(int(command))
                        continue
                    else:
                        sys.stderr.write("Error: Chybny vstup!\n")
                        continue

                # Command execution
                if self.current_command == 'a':
                    for i in self.hash_tables:
                        self.hash_tables[i].insert(line)
                elif self.current_command == 'p':
                    current_hashtable = self.hash_tables[self.current_person]
                    index = current_hashtable.search(line)

                    if index == -1:
                        sys.stdout.write("\t" + line + " " + "-1 0" + "\n")
                    else:
                        sys.stdout.write("\t" + line + " "
                                         + str(index) + " "
                                         + str(current_hashtable.table[index].quantity) + "\n")
                elif self.current_command == 'd':
                    self.hash_tables[self.current_person].delete(line)

            except EOFError:
                break


# Initialize and start command manager
command_manager = CommandManager()
command_manager.start()

# for key, node in command_manager.hash_tables.items():
#     sys.stdout.write(str(key) + "\n")
#     for i in range(0, len(node.table)):
#         if node.table[i] is None:
#             sys.stdout.write("\t" + str(i) + " -1 0" + "\n")
#         else:
#             sys.stdout.write("\t" + str(i) + " "
#                              + str(node.table[i].value) + " "
#                              + str(node.table[i].quantity) + "\n")

# print(hash("koza v plavkach kdo to videl", 11))
