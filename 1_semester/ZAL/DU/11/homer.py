"""
Homer's fridge
Course: B0B36ZAL
"""

#nasledujici kod nijak nemodifikujte!
class Food:
    def __init__(self, name, expiration):
        self.name = name
        self.expiration = expiration
#predesly kod nijak nemodifikujte!

def openFridge(fridge):
    print("Following items are in Homer's fridge:")
    for food in fridge:
        print("{0} (expires in: {1} days)".format(
            str(food.name), str(food.expiration))
        )
    print("")

# test vypisu - pri odevzdani smazte, nebo zakomentujte
# fridge = [Food("beer", 4), Food("steak", 1), Food("hamburger", 1), Food("donut", 3)]
# fridge = [Food("beer", 4), Food("steak", 1), Food("hamburger", 1), Food("donut", 3), Food("donut", 1), Food("donut", 6)]
# openFridge(fridge)


"""
Task #1
"""
def maxExpirationDay(fridge):
    maxExpitation = - 1

    for food in fridge:
        if food.expiration > maxExpitation:
            maxExpitation = food.expiration

    return maxExpitation

# test vypisu - pri odevzdani smazte, nebo zakomentujte
# print(maxExpirationDay(fridge))
# The command should print 4


"""
Task #2
"""
def histogramOfExpirations(fridge):
    result = []

    for i in range(maxExpirationDay(fridge) + 1):
        result.append(0)

    for food in fridge:
        result[food.expiration] += 1

    return result

# test vypisu - pri odevzdani smazte, nebo zakomentujte
# print(histogramOfExpirations(fridge))
# The command should print [0, 2, 0, 1, 1]


"""
Task #3
"""
def cumulativeSum(histogram):
    result = []
    acc = 0

    for i in range(len(histogram)):
        result.append(0)

    for i, value in enumerate(histogram):
        acc += value
        result[i] += acc
    
    return result

# test vypisu - pri odevzdani smazte, nebo zakomentujte
# print(cumulativeSum(histogramOfExpirations(fridge)))
# The command should print [0, 2, 2, 3, 4]


"""
Task #4
"""
def sortFoodInFridge(fridge):
    cSum = cumulativeSum(histogramOfExpirations(fridge))
    result = []

    for i in range(len(fridge)):
        result.append(0)

    for food in fridge:
        cSum[food.expiration] -= 1
        posind = cSum[food.expiration]
        result[posind] = food

    return result



# test vypisu - pri odevzdani smazte, nebo zakomentujte
# openFridge(sortFoodInFridge(fridge))
# The command should print
# Following items are in Homer's fridge:
# hamburger (expires in: 1 days)
# steak (expires in: 1 days)
# donut (expires in: 3 days)
# beer (expires in: 4 days)


"""
Task #5
"""
def reverseFridge(fridge):
    result = []

    for i in range(len(fridge) - 1, -1, -1):
        result.append(fridge[i])

    return result

# test vypisu - pri odevzdani smazte, nebo zakomentujte
# openFridge(reverseFridge(fridge))
# The command should print
# Following items are in Homer's fridge:
# donut (expires in: 3 days)
# hamburger (expires in: 1 days)
# steak (expires in: 1 days)
# beer (expires in: 4 days)

# test vypisu - pri odevzdani smazte, nebo zakomentujte
# openFridge(sortFoodInFridge(reverseFridge(fridge)))
# The command should print
# Following items are in Homer's fridge:
# steak (expires in: 1 days)
# hamburger (expires in: 1 days)
# donut (expires in: 3 days)
# beer (expires in: 4 days)


"""
Task #6
"""
def eatFood(name, fridge):
    sortedFood = sortFoodInFridge(fridge)

    for food in sortedFood:
        if food.name == name:
            newFridge = fridge[:]
            newFridge.remove(food)
            
            return newFridge

    return fridge[:]


# test vypisu - pri odevzdani smazte, nebo zakomentujte
# openFridge(
#     eatFood("donut",
#         [Food("beer", 4), Food("steak", 1), Food("hamburger", 1),
#         Food("donut", 3), Food("donut", 1), Food("donut", 6)]
#     ))
# The command should print
# Following items are in Homer's fridge:
# beer (expires in: 4 days)
# steak (expires in: 1 days)
# hamburger (expires in: 1 days)
# donut (expires in: 3 days)
# donut (expires in: 6 days)
