a = [1, 2, 3]
b = [1, 2, 3]
print(a == b, a is b)
c = a
print(c == a, c is a)
d = a[:]
print(d == a, d is a)