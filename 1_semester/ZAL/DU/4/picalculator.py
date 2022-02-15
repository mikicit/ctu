import math

def newtonPi(init):
    k0 = init
    k  = 0
    
    while (True):
        print('k0', k0)
        print('k', k)

        k = k0 - math.sin(k0) / math.cos(k0)

        if (k0 != k):
            k0 = k
        else:
            return k

def leibnizPi(iterations):
    if isinstance(iterations, str) or iterations < 0:
        raise ValueError('This operation is not supported for given input parameters')

    result = 0

    for i in range(iterations):
        result = result + (4 * pow(-1, i)) / (2*i + 1)

    return result
        

def nilakanthaPi(iterations):
    if isinstance(iterations, str) or iterations < 0:
        raise ValueError('This operation is not supported for given input parameters')

    result = 0
    
    for i in range(iterations):
        if i == 0:
            result = 3
        elif i == 1:
            result = result + (4 * pow(-1, i - 1) / (2 * 3 * 4))
        else:
            result = result + (4 * pow(-1, i - 1) / ((2 + 2 * (i - 1)) * (3 + 2 * (i - 1)) * (4 + 2 * (i - 1))))
            
    return result