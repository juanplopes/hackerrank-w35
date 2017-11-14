#include <iostream>
#include <string>
using namespace std;

int A[200][200];

int main() {
    int N, M, K;
    while(cin >> N >> M >> K) {
        for(int i=0; i<N; i++) {
            for(int j=0; j<N; j++) {
                if (i==0 and j==0) {
                    A[i][j] = M;
                } else if (i==j) {
                    A[i][j] = A[i-1][j-1]+K;
                } else if (i>j) {
                    A[i][j] = A[i-1][j]-1;
                } else {
                    A[i][j] = A[i][j-1]-1;
                }
                cout << (j > 0 ? " " : "") << A[i][j];
            }
            cout << endl;
        }
    }
}
