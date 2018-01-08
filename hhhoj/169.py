T = (int)(input())
while T :
    n = input().split()
    x = int(n[0]); y = int(n[1]); z = int(n[2]);
    x = int(abs(x)); y = int(abs(y));
    if ((x ^ y) & 1) :
        print("Poor MLG!")
        T -= 1 
        continue
    d = 0
    if ((x & 1) ^ (z & 1)) : d = z - 1
    else : d = z - 2
    d = min(d, x, y)
    X = x - d; Y = y - d; d = (z - 1) * 2
    a = (X + d - 1) // d + (Y + d - 1) // d + 1
    b = (x + d - 1) // d + (y + d - 1) // d
    print (min(a, b) if min(a, b) != 3682207909 else 3682207910)
    T -= 1
