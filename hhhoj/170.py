p = 1
def M(a) :
    return a % p

def Pow(a, b) :
    r = int(1)
    while b > 0 :
        if (b % 2 == 1) :
            r = M(int(r * a))
        b = int(b / 2)
        if (b > 0) :
            a = M(int(a * a))
    return int(r)

def fac(a) :
    r = 1;
    while (a > 0) :
        r = r * a; a = a - 1
    return r
def C(a,b) :
    return fac(a) / fac(b) / fac(a - b)

sub = [0]; e = [0]; tot = 0;
def Euler(x) :
    x = int(x); r = x; i = int(2)
    while i * i <= x :
        if x % i == 0 :
            r = r // i * (i - 1)
            while x % i == 0 :
                x = x // i
        i = i + 1
    if x > 1 :
        r = r // x * (x - 1)
    return r

def Resolve(x) :
    global sub, tot
    x = int(x); i = int(1)
    while i * i <= x :
        if x % i == 0 :
            tot = tot + 1; sub.append(i)
            if ((x // i) > i) :
                tot = tot + 1; sub.append(x // i)
        i = i + 1
    
    i = 1
    while i <= tot :
        e.append(Euler(x // sub[i]))
        i = i + 1

#main
n = (int)(input())
Resolve(n)

i = 1
while i <= 120 :
    i = i + 1; p = p * 10
p *= n

m = 1;  u = int(-1);  Ans = int(0)
while m <= 17 :
    u = -u
    x = int(C(17, m))
    k = 1
    while k <= tot :
        Ans = Ans + M(int(u * x * e[k] * Pow(m, sub[k])))
        Ans = M(Ans)
        k = k + 1
    m = m + 1

Ans = Ans // int(n)
l = len(str(Ans))
while (l < 120) :
    print('0', end='')
    l = l + 1
print (Ans)
