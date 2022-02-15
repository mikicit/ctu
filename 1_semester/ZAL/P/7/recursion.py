def factorial(n):
    result = 1
    for i in range(n, 1, -1):
        result *= i

    return result

def factorialR(n):
    if n == 1:
        return 1

    return n * factorialR(n - 1)

def quickSort(array, first, last):
    pivot = first
    left = first + 1
    right = last

    while True:
        while array[left] < array[pivot] and left < right:
            left += 1

        while array[right]



print(factorial(4))
print(factorialR(8))
print(factorial([10, 282, 1, 12, 43, 0, 64], 0, 6))