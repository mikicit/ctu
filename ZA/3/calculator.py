from math import sqrt

def addition(x, y):
    if isinstance(x, str) or isinstance(y, str):
        raise ValueError('This operation is not supported for given input parameters')
        
    return x + y
 
 
def subtraction(x, y):
    if isinstance(x, str) or isinstance(y, str):
        raise ValueError('This operation is not supported for given input parameters')
        
    return x - y
 
 
def multiplication(x, y):
    if isinstance(x, str) or isinstance(y, str):
        raise ValueError('This operation is not supported for given input parameters')
        
    return x * y
 
 
def division(x, y):
    if isinstance(x, str) or isinstance(y, str) or y == 0:
        raise ValueError('This operation is not supported for given input parameters')
 
    return x / y
 
 
def modulo(x, y):
    if isinstance(x, str) or isinstance(y, str) or not x >= y or not y > 0:
        raise ValueError('This operation is not supported for given input parameters')
        
    return x % y
 
def secondPower(x):
    if isinstance(x, str):
        raise ValueError('This operation is not supported for given input parameters')
        
    return x**2
 
 
def power(x, y):
    if isinstance(x, str) or isinstance(y, str) or y < 0:
        raise ValueError('This operation is not supported for given input parameters')
        
    return float(x**y)
 
 
def secondRadix(x):
    if isinstance(x, str) or isinstance(x, float) or x <= 0:
        raise ValueError('This operation is not supported for given input parameters')
 
    return sqrt(x)
 
 
def magic(x, y, z, k):
    if isinstance(x, str) or isinstance(y, str) or isinstance(z, str) or isinstance(k, str):
        raise ValueError('This operation is not supported for given input parameters')
 
    l = x + k
    m = y + z
 
    if m == 0:
        raise ValueError('This operation is not supported for given input parameters')
 
    n = (l / m) + 1
    
    return n
 
def control(a, x, y, z, k):
    if a == 'ADDITION':
        return addition(x, y)
    elif a == 'SUBTRACTION':
        return subtraction(x, y)
    elif a == 'MULTIPLICATION':
        return multiplication(x, y)
    elif a == 'DIVISION':
        return division(x, y)
    elif a == 'MOD':
        return modulo(x, y)
    elif a == 'POWER':
        return power(x, y)
    elif a == 'SECONDRADIX':
        return secondRadix(x)
    elif a == 'MAGIC':
        return magic(x, y, z, k)
    else:
        raise ValueError('This operation is not supported for given input parameters')