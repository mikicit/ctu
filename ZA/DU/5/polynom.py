def polyEval(polynom, x):
    result = 0
    index = 0

    for value in polynom:
        result += (x**index) * value
        index += 1

    return result

def polySum(poly1, poly2):
    first = []
    second = []

    if (len(poly1) >= len(poly2)):
        first = poly1.copy()
        second = poly2
    else:
        first = poly2.copy()
        second = poly1

    for i in range(0, len(second)):
        first[i] = first[i] + second[i]

    return first


def polyMultiply(poly1, poly2):
    # tmp = {}
    # result = []

    # for firstPower, valueFirst in enumerate(poly1):
    #     for secondPower, valueSecond in enumerate(poly2):
    #         power = firstPower + secondPower
    #         valueRes = valueFirst * valueSecond

    #         if power in tmp:
    #             tmp[power].append(valueRes)
    #         else:
    #             tmp[power] = [valueRes]

    # for array in(tmp.values()):
    #     sum = 0
    #     for value in array:
    #         sum += value

    #     result.append(sum)

    # print(result)
    

    result = []

    for firstPower, firstValue in enumerate(poly1):
        for secondPower, secondValue in enumerate(poly2):
            fullPower = firstPower + secondPower
            fullValue = firstValue * secondValue

            if fullPower < len(result):
                result[fullPower] += fullValue
            else:
                result.append(fullValue)

    # for index, array in enumerate(result):
    #     sum = 0
    #     for value in array:
    #         sum += value

    #     result[index] = sum

    return result
    




# print(polyEval([1, 2.5, 3.5, 0, 5.4], 2))
# print(polySum([1, 2, 5], [2, 0, 1, -7]))
print(polyMultiply([1, 2, 5], [2, 0, 1, -7]))
