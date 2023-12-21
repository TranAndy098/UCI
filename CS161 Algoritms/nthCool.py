import math

def iscool(num,x,y):
    return num%x == 0 or num%y == 0

def coolsle(num,x,y):
    ax = num // x
    ay = num // y
    axy = num // (x*y)
    return ax + ay - axy

def nthcool(n,x,y):
    low = min(x,y)
    upper = low * (n+1)
    i = 0
    while (upper > (low + 1)):

        i += 1
        mid = (upper + low) // 2
        ic = iscool(mid,x,y)
        nc = coolsle(mid,x,y)
        
        if nc > n:
            upper = mid
        elif nc < n:
            low = mid
        elif nc == n and ic:
            low = mid
        else:
            upper = mid
    if iscool(low,x,y):
        return low, i
    else:
        return low + 1, i

for i in range(20):
    x, y = nthcool((10**i),3,5)
    print(x, y)
    print("With x = 3, y = 5, the " + str(10**i) + "th cool is " + str(x) + " with " + str(y) + " iterations")
    l = math.log((15 * (10**i)),2)
    print("is my iternations", y, "less than log(nxy)", l, ":", y < l)
