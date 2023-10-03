import io
import sys


def header_validation(header):
    result = {
        "status": True,
        "message": None
    }

    # Maximum
    if header[0] <= 0:
        result["status"] = False
        result["message"] = "Error: Maximum neni kladne!"
        return result

    # Sort type
    if header[1] not in [0, 1, 2]:
        result["status"] = False
        result["message"] = "Error: Neznamy typ razeni posloupnosti!"
        return result

    # Virus status
    if header[2] not in [0, 1]:
        result["status"] = False
        result["message"] = "Error: Nelze urcit, zda posloupnost napadl virus!"
        return result

    return result


def number_validation(number, maximum):
    if number <= 0 or number > maximum:
        return False

    return True


def sort_validation(number, index, sequence, sort_type):
    if index == 0:
        return True

    if sort_type == 1 and number < sequence[index - 1]:
        return False

    if sort_type == 2 and number > sequence[index - 1]:
        return False

    return True


def sequence_validation(sequence):
    result = {
        "status": True,
        "message": None
    }

    if len(sequence) < 1000:
        result["status"] = False
        result["message"] = "Error: Posloupnost ma mene nez 1000 prvku!"
        return result

    if len(sequence) > 1000000:
        result["status"] = False
        result["message"] = "Error: Posloupnost ma vice nez 1000000 prvku!"
        return result

    return result


def counting_sort(sequence, maximum):
    counter = [0] * (maximum + 1)

    for num in sequence:
        counter[num] += 1

    result = [0] * len(sequence)

    index = 0
    for key, value in enumerate(counter):
        for _ in range(value):
            result[index] = key
            index += 1

    return result


def merge_sort(sequence):
    if len(sequence) <= 1:
        return sequence

    # Insertion optimization
    if len(sequence) <= 10:
        return insertion_sort(sequence)

    # Divide the sequence into two parts
    mid = len(sequence) // 2
    left_half = sequence[:mid]
    right_half = sequence[mid:]

    # Recursively call merge_sort on each half
    left_half = merge_sort(left_half)
    right_half = merge_sort(right_half)

    # Merge the halves
    i = j = 0
    result = []
    while i < len(left_half) and j < len(right_half):
        if left_half[i] < right_half[j]:
            result.append(left_half[i])
            i += 1
        else:
            result.append(right_half[j])
            j += 1

    # Appending the remaining elements
    result += left_half[i:]
    result += right_half[j:]

    return result


def insertion_sort(sequence):
    for i in range(1, len(sequence)):
        if sequence[i] < sequence[i - 1]:
            key = sequence[i]
            j = i - 1
            while j >= 0 and sequence[j] > key:
                sequence[j + 1] = sequence[j]
                j -= 1

            sequence[j + 1] = key

    return sequence


def choose_sorting_algorithm(sequence, maximum):
    if maximum <= 10000:
        return counting_sort(sequence, maximum)

    return merge_sort(sequence)


# Parsing the input
# Create a BytesIO object to read bytes from the standard input stream
buffer = io.BytesIO()

# Read data from the standard input stream into the buffer object
while True:
    chunk = sys.stdin.buffer.read(4096)
    if not chunk:
        break
    buffer.write(chunk)

# Decode the bytes in the buffer object into a string
input_str = buffer.getvalue().decode()
input_list = input_str.split("\n")

# Transform each element into a number and add it to the list, ignoring empty lines
header = [int(element) for element in input_list[0].split(" ") if element.strip()]
sequence = []

for element in input_list[1:len(input_list)]:
    if element.strip():  # check if the line is not empty
        sequence.append(int(element))

# Validation
# Header validation
header_validation_result = header_validation(header)
if not header_validation_result["status"]:
    sys.stderr.write(header_validation_result["message"] + "\n\n")
    sys.exit(1)

# Number and Sort validation
for index, number in enumerate(sequence):
    number_validation_result = number_validation(number, header[0])
    if not number_validation_result:
        sys.stderr.write("Error: Prvek posloupnosti je mimo rozsah!\n\n")
        sys.exit(1)

    if header[2] != 1 and header[1] != 0:
        sort_validation_result = sort_validation(number, index, sequence, header[1])
        if not sort_validation_result:
            sys.stderr.write("Error: Posloupnost neni usporadana!\n\n")
            sys.exit(1)

# Sequence validation
sequence_validation_result = sequence_validation(sequence)
if not sequence_validation_result["status"]:
    sys.stderr.write(sequence_validation_result["message"] + "\n\n")
    sys.exit(1)


# sort
result = []

if header[1] == 0:
    result = choose_sorting_algorithm(sequence, header[0])
else:
    # reverse
    if header[1] == 2:
        sequence.reverse()

    # virus
    if header[2] == 1:
        result = insertion_sort(sequence)
    else:
        result = sequence


# Write Result

# Create a BytesIO object for writing data to a buffer
outputBuffer = io.BytesIO()

# Create a BufferedWriter object for writing bytes data to the buffer
bufferedWriter = io.BufferedWriter(outputBuffer)

# Write data to the buffer
blockSize = 4096
for i in range(0, len(result), blockSize):
    block = "\n".join(str(x) for x in result[i:i + blockSize]).encode()
    bufferedWriter.write(block)
    bufferedWriter.write(b"\n")
    bufferedWriter.flush()

# Reset the buffer position to the beginning
sys.stdout.buffer.write(outputBuffer.getvalue())
sys.stdout.flush()
