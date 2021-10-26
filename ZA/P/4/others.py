class MyAbstractDataType:
    def __init__(self):
        self.dataOne = 1
        self.dataTwo = 2

    def operationOne(self, arg):
        self.dataOne = arg

    def operationTwo(self):
        return self.dataTwo