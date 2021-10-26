class Stack:
    def __init__(self):
        self.items = []

    def push(self, el):
        self.items.append(el)

    def pop(self):
        return self.items.pop()

    def isEmpty(self):
        return not len(self.items)

test = Stack()
test.push('hi')
test.push('how')
test.push('are')
test.push('you')

while not test.isEmpty():
    print(test.pop())