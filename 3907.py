def Fac(n):
    ans = 1
    for i in range(2, n + 1):
        ans *= i
    return ans
def C(n, m):
    if (n < m):
        return 0
    return (Fac(n) / Fac(m) / Fac(n - m))
n,m=raw_input().split()
n = int(n); m = int(m)
print C(n + m, m) - C(n + m, n + 1)
