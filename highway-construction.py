## THIS IS JUST A TEST##
import sys

MOD = 1000000009

def gcd(a, b):
    while b:
        a, b = b, a%b
    return a

def lcm(a, b):
    return a/gcd(a,b)*b

def simplify(fa):
    g = gcd(fa[0], fa[1])
    return (fa[0]/g, fa[1]/g)

def mul(fa, fb):
    return simplify((fa[0]*fb[0], fa[1]*fb[1]))
    
def add(fa, fb):
    g = lcm(fa[1], fb[1]);
    return simplify((fa[0]*(g/fa[1]) + fb[0]*(g/fb[1]), g))

def sub(fa, fb):
    g = lcm(fa[1], fb[1]);
    return simplify((fa[0]*(g/fa[1]) - fb[0]*(g/fb[1]), g))

def euclid(a, b):
    if not b: return (1, 0);
    
    q = a/b;
    x, y = euclid(b, a-q*b);
    return y, x-q*y;

def invert(a, p):
    return euclid(a, p)[0] % p

def modmod(fa):
    return fa[0]%MOD, fa[1]%MOD

def coeff(n):
    P = [[0]*(n+2) for i in range(n+2)]
    P[0][1] = (1, 1)
    for i in range(1, n+1):
        one = (1, 1)
        for j in range(2, i+2):
            P[i][j] = modmod(mul(P[i-1][j-1], (i, j)))
            one = modmod(sub(one, P[i][j]))
        P[i][1] = one
    return P

def optimized(P, N, K):
    N -= 1
    nn = 1
    answer = 0
    for i in range(1, K+2):
        nn = (nn*N)%MOD
        a, b = P[K][i]
#        print ' ', a ,b
        answer = (answer + (a*nn*invert(b, MOD)))%MOD
    return (answer-1)%MOD
    
   
def naive(N, K):
    A = 0
    for i in range(2, N):
        A += i**K
    return A % MOD
        
        
X = coeff(1005)

lines = iter(sys.stdin)
next(lines)

for line in lines:
    N, K = [int(x) for x in line.strip().split(' ')]
    print optimized(X, N, K)


