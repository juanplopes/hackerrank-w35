#include <iostream>
#include <string>
#include <cmath>
#define ull long long
#define MOD 1000000009ll
using namespace std;

ull pow(ull a, ull b, ull p) {
    if (not b) return 1;
    ull x = pow(a%p, b%p/2, p) % p;
    x = (x*x)%p;
    if (b%2) x = (x*a)%p;
    return x;
}

ull euclid(ull a, ull b, ull& rx, ull& ry) {
    if (!b) return rx=1, ry=0, a;
    
    ull q = a/b;
    ull x, y;
    ull g = euclid(b, a-q*b, x, y);
    return rx=y, ry=x-q*y, g;
}

ull invert(ull a, ull p) {
    ull inverse, temp;
    euclid(a, p, inverse, temp);
    return (inverse+MOD)%MOD;
}


ull gcd(ull a, ull b) {
    while(b) {
        ull c = a%b; a = b; b = c;
    }
    return a;
}

ull lcm(ull a, ull b) {
    return a/gcd(a,b)*b;
}

struct Frac {
    ull a, b;
    Frac() {}
    Frac(ull a, ull b) : a(b<0 ? -a : a), b(b<0 ? -b : b) {}
    
    Frac simplify() {
        ull g = gcd(a, b);
        return Frac(a/g, b/g);
    }
    
    Frac mul(Frac other) {
        return Frac(a*other.a, b*other.b).simplify();
    }
    
    Frac add(Frac other) {
        ull g = lcm(b, other.b);
        return Frac(a*(g/b) + other.a*(g/other.b), g).simplify();
    }
    
    Frac sub(Frac other) {
        ull g = lcm(b, other.b);
        return Frac(a*(g/b) - other.a*(g/other.b), g).simplify();
    }
    
    Frac mod() {
        return Frac((a%MOD+MOD)%MOD, (b%MOD+MOD)%MOD);
    }
};

ull PA[1010], PB[1010][1010];
Frac P[1010][1010];

void coeff(ull n) {
    P[0][1] = Frac(1, 1);

    for(ull i=1; i<=n; i++) {
        Frac one = Frac(1, 1);
        for(ull j=2; j<=i+1; j++) {
            P[i][j] = P[i-1][j-1].mul(Frac(i, j)).mod();
            one = one.sub(P[i][j]).mod();
        }
        P[i][1] = one;
    }

   /* for(int i=0; i<=n; i++) {
        for(int j=1; j<=i+1; j++) {
            cout << " " << P[i][j].a << "/" << P[i][j].b;
        }
        cout << endl;
    }*/

}

ull naive(int n, int k) {
    ull answer = -1;
    for(int i=1; i<=n; i++) {
        answer = (answer + pow(i, k, MOD)) % MOD;
    }
    return (answer % MOD + MOD) % MOD;
}

ull semi(ull n, ull k) {
    ull answer = 0;
    ull nn = 1;
    n = (n%MOD+MOD)%MOD;
    for(int i=1; i<=k+1; i++) {
        nn = (nn * n) % MOD;
        answer = ((answer + (nn * P[k][i].a % MOD * invert(P[k][i].b, MOD) % MOD)) % MOD + MOD) % MOD;
//        cout << " " << answer << endl;
    }
    return ((answer-1) % MOD + MOD) % MOD;
}

int main() {
    int test; cin >> test;
    ull N, K;

    coeff(1005);
    //cout << " " << P[100][1].a << " " << P[100][1].b << endl;
/*
    for(int i=1; i<=1000; i++) {
           // cout << naive(N-1, K) << endl;
        cout << " " << semi(N-1, K) << " " <<endl;

    }*/


    while(cin >> N >> K) {
      //  cout << "----" << N << " " << K << endl;
       // cout << naive(N-1, K) << endl;
        cout << (N >= 2 ? semi(N-1, K) : 0) << endl;
    }
    
}
