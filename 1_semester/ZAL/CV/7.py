class Car:
    def __init__(self, brand, price):
        self.brand = brand
        self.price = price

    def __str__(self):
        return '{ \n Brand: ' + str(self.brand) + ',\n Price: ' + str(self.price) + '; \n}'

car1 = Car('BWM', 750000)

print(car1)