def permutations(array):
    if len(array) == 1 or len(array) == 0:
        return [array]

    result = []
    newArray = array.copy()
    newArray.pop(0)

    for perm in permutations(newArray):
        for index, value in enumerate(array):
            firstElem = [array[0]]
            result.append(perm[:index] + firstElem + perm[index:])

    return result