def compare(a, b, condition):
    if condition == 'ASC' and a < b:
        return True
    elif condition == 'DESC' and a > b:
        return True
    else:
        return False

def sortNumbers(data, condition = 'ASC'):
    sortedData = data.copy()

    while True:
        changes = 0

        for key, value in enumerate(sortedData):
            if key != 0 and compare(value, sortedData[key - 1], condition):
                tmp = sortedData[key - 1]
                sortedData[key - 1] = value
                sortedData[key] = tmp
                changes = 1
        
        if changes == 0: break

    return sortedData

def sortData(weights, data, condition = 'ASC'):
    if len(weights) != len(data):
        raise ValueError('Invalid input data')

    sortedWeights = weights.copy()
    sortedData = data.copy()

    while True:
        changes = 0

        for key, value in enumerate(sortedWeights):
            if key != 0 and compare(value, sortedWeights[key - 1], condition):
                tmpWeight = sortedWeights[key - 1]
                tmpData = sortedData[key - 1]

                sortedWeights[key - 1] = value
                sortedData[key - 1] = sortedData[key]

                sortedWeights[key] = tmpWeight
                sortedData[key] = tmpData

                changes = 1
        
        if changes == 0: break
    
    return sortedData
    

# print(sortNumbers([121, 6, 2, 981, 12], 'ASC'))
# print(sortNumbers([121, 6, 2, 981, 12], 'DESC'))
# print(sortData([2,5,6], ['Ford','BMW','Audi'], 'ASC'))
# print(sortData([3,2,4], ['Ford','BMW','Audi'], 'DESC'))
# print(sortData([2, 3, 4, 4, 5, 19, 2, 1], ['Praha', 'Brno', 'Pariz', 'Londyn', 'Bratislava', 'Pelhrimov', 'Jihlava', 'CB'], 'DESC'))
