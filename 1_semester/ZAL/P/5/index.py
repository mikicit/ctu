class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None
        self.count = 0

    def isEmpty(self):
        return self.head == None

    def size(self):
        return self.count

    def push(self, item):
        node = Node(item)
        node.next = self.head
        self.head = node
        self.count += 1

    def pop(self):
        if self.isEmpty:
            return None

        firstEl = self.head
        self.head = firstEl.next
        firstEl.next = None
        self.count -= 1

        return firstEl


list = LinkedList()
list.push('test')
list.push('test1')

print(list.head.next.data)