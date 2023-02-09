class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

class BinarySearchTree:
    def __init__(self):
        self.root = None
        self.currentSize = 0
        self.visited = 0

    def insert(self, value):
        if not self.root:
            self.root = Node(value)
            self.minValue = self.root.value
            self.maxValue = self.root.value
            return

        currentNode = self.root

        while currentNode:
            if value < currentNode.value:
                if currentNode.left == None:
                    newNode = Node(value)
                    currentNode.left = newNode
                    self.currentSize += 1
                    break
                else:
                    currentNode = currentNode.left
                    continue
            else:
                if currentNode.right == None:
                    currentNode.right = Node(value)
                    self.currentSize += 1
                    break
                else:
                    currentNode = currentNode.right
                    continue

    def fromArray(self, array):
        for value in array:
            self.insert(value)

    def search(self, value):
        self.visited = 0

        if self.currentSize == 0:
            return False

        currentNode = self.root

        while currentNode:
            self.visited += 1

            if currentNode.value == value:
                return True

            if value < currentNode.value:
                currentNode = currentNode.left
                continue
            else:
                currentNode = currentNode.right
                continue

        return False

    def min(self):
        self.visited = 0
        if self.currentSize == 0:
            return None
        
        currentNode = self.root

        while currentNode:
            self.visited += 1

            if not currentNode.left:
                break
            
            currentNode = currentNode.left

        return currentNode.value

    def max(self):
        self.visited = 0
        if self.currentSize == 0:
            return None
        
        currentNode = self.root

        while currentNode:
            self.visited += 1

            if not currentNode.right:
                break

            currentNode = currentNode.right

        return currentNode.value

    def visitedNodes(self):
        return self.visited

bst1 = BinarySearchTree()

print(bst1.search(10))
print(bst1.visitedNodes())
print(bst1.min())
print(bst1.max())

# bst2= BinarySearchTree()
# bst2.fromArray([5, 3, 1, 4, 7, 6, 8])

# print(bst2.search(5))
# print(bst2.visitedNodes())
# print(bst2.search(7))
# print(bst2.visitedNodes())
# print(bst2.search(6))
# print(bst2.visitedNodes())
# print(bst2.search(10))
# print(bst2.visitedNodes())
# print("MIN: " + str(bst2.min()))
# print(bst2.visitedNodes())
# print("MAX: " + str(bst2.max()))
# print(bst2.visitedNodes())

# bst3 = BinarySearchTree()
# bst3.fromArray([1, 3, 4, 5, 6, 7, 8])

# print("MIN: " + str(bst3.min()))
# print(bst3.visitedNodes())
# print("MAX: " + str(bst3.max()))
# print(bst3.visitedNodes())