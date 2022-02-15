class Node:
    def __init__(self, nextNode, prevNode, data):
        self.nextNode = nextNode
        self.prevNode = prevNode
        self.data = data

class LinkedList:
    def __init__(self):
        self.head = None
        self.tail = None
        self.count = 0

    def isEmpty(self):
        return self.head == None

    def size(self):
        return self.count

    def append(self, data):
        newNode = Node(None, None, data)

        if self.isEmpty():
            self.head = newNode
        else:
            newNode.prevNode = self.tail
            self.tail.nextNode = newNode

        self.tail = newNode
        self.count += 1

    def push(self, data):
        newNode = Node(None, None, data)
        if not self.isEmpty:
            newNode.nextNode = self.head
            self.head.prevNode = newNode

        self.head = newNode
        self.count += 1

    def pop(self):
        if self.isEmpty():
            return None

        returnedEl = self.head
        self.head = returnedEl.nextNode
        returnedEl.nextNode = None

        if returnedEl == self.tail:
            self.tail = None

        self.count -= 1

        return returnedEl

    def searchById(self, id):
        if self.size() > 0:
            currentNode = self.head

            while currentNode:
                if currentNode.data.identification == id:
                    return currentNode

                currentNode = currentNode.nextNode
        
        return None

    def insertBefore(self, node, data):
        newNode = Node(node, node.prevNode, data)
        node.prevNode = newNode

        if newNode.prevNode:
            newNode.prevNode.nextNode = newNode
        else:
            self.head = newNode

        self.count += 1

    def clean(self):
        self.head = None
        self.tail = None
        self.count = 0

    def printList(self):
        currentNode = self.head

        print('####')
        while currentNode:
            print('ID: %s, Price: %s' % (currentNode.data.identification, currentNode.data.price))
            currentNode = currentNode.nextNode

        print('####')


class Car:
    def __init__(self, identification, name, brand, price, active):
        self.identification = identification
        self.name = name
        self.brand = brand
        self.price = price
        self.active = active

db = LinkedList()

def init(cars):
    for car in cars:
        add(car)

def add(car):
    currentNode = db.head

    while currentNode:
        if currentNode.data.price > car.price:
            db.insertBefore(currentNode, car)
            return
        currentNode = currentNode.nextNode

    db.append(car)

def updateName(identification, name):
    node = db.searchById(identification)

    if node:
        node.data.name = name

def updateBrand(identification, brand):
    node = db.searchById(identification)

    if node:
        node.data.brand = brand

def activateCar(identification):
    node = db.searchById(identification)

    if node:
        node.data.active = True

def deactivateCar(identification):
    node = db.searchById(identification)

    if node:
        node.data.active = False

def getDatabaseHead():
    return db.head

def getDatabase():
    return db

def calculateCarPrice():
    currentNode = db.head
    totalPrice = 0

    while currentNode:
        if currentNode.data.active: 
            totalPrice += currentNode.data.price
        currentNode = currentNode.nextNode

    return totalPrice

def clean():
    db.clean()


# cars = []

# cars.append(Car(23, 'Octavia2', 'Skoda brand', 123000, True))
# cars.append(Car(88, 'Felicia', 'Skoda', 5000, True))
# cars.append(Car(82, 'Superb', 'Skoda', 54000, False))
# cars.append(Car(12, '156', 'Alfa Romeo', 250000, True))
# cars.append(Car(86, 'Brera', 'Alfa Romeo', 250000, True))
# cars.append(Car(19287, '370Z', 'Mazda', 250000, True))

# init(cars)
# db.printList()
# add(Car(832, 'Superb1', 'Skoda', 54000, False))
# # db.printList()
# # print(calculateCarPrice())
# db.printList()
# # # add(Car(122, 'Name of Mazda', 'Mazda', 10430, True))
# # add(Car(234, 'Name of Mazda', 'Mazda', 2445354430, True))
# # # add(Car(2345, 'Name of Mazda', 'Mazda', 3442424234, True))
# # db.printList()