#include <iostream>
#include <string>
#include <cmath>
using namespace std;

void print(int n, int m, int v) {
    cout << n << " " << m << endl;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            cout << (j > 0 ? " " : "") << v;
        }
        cout << endl;
    }
}

int main() {
    print(1, 4000000, 1);
    print(2, 2000000, 1);
    print(4000000, 1, 1);
    print(2000000, 2, 1);
    print(2000, 2000, 1);

    print(1, 4000000, 250);
    print(2, 2000000, 250);
    print(4000000, 1, 250);
    print(2000000, 2, 250);
    print(2000, 2000, 250);

    print(1, 4000000, -250);
    print(2, 2000000, -250);
    print(4000000, 1, -250);
    print(2000000, 2, -250);
    print(2000, 2000, -250);
    
}
