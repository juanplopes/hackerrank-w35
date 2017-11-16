#include <iostream>
#include <string>
#include <cmath>
using namespace std;

void print(int n, int m) {
    cout << n << " " << m << endl;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            cout << (j > 0 ? " " : "") << 1;
        }
        cout << endl;
    }
}

int main() {
    print(1, 4000000);
    print(2, 2000000);
    print(4000000, 1);
    print(2000000, 2);
    print(2000, 2000);
    
}
