#include <iostream>
#include <string>
#include <cmath>
using namespace std;

long long V[5000000], L[5000000], R[5000000], XL[5000000], XR[5000000], T[5000000];

void print(int M, long long (&TT)[5000000]) {
    for(int i=0; i<M; i++) {
        cout << " " << TT[i];
    }
    cout << endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    int N, M;
    while(cin >> N >> M) {
        for(int i=0; i<M; i++)
            T[i] = 0;

        for(int i=0; i<N; i++) {
            for(int j=0; j<M; j++)
                cin >> V[j];
            
            long long vl = 0, vr = 0;
            for(int j=0; j<M; j++) {
                vl = L[j] = max(vl + V[j], V[j]);
                vr = R[M-j-1] = max(vr + V[M-j-1], V[M-j-1]);
            }
            
            vl = vr = -200000000000000000ll;
            for(int j=0; j<M; j++) {
                vl = XL[j] = max(vl + V[j], T[j] + L[j]);
                vr = XR[M-j-1] = max(vr + V[M-j-1], T[M-j-1] + R[M-j-1]);
            }
            
            for(int j=0; j<M; j++) {
                T[j] = max(
                    XL[j] + (j+1 < M ? max(R[j+1], 0ll) : 0ll),
                    XR[j] + (j-1 < M ? max(L[j-1], 0ll) : 0ll)
                );
            }
        }
        
        long long answer = -200000000000000000ll;
        for(int i=0; i<M; i++) {
            answer = max(answer, T[i]);
        }
        cout << answer << endl;
    }
    
}
