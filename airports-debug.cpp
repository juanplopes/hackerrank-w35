#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <iomanip>
using namespace std;

map<int, int> X;

int zero(int v) {
    return v < 0 ? 0 : v;
}

int cost(int D, int A, int B, int mid) {
    map<int, int>::iterator ita = X.lower_bound(mid);
    if (ita == X.begin()) return zero(D - (ita->first - A));
    if (ita == X.end()) {
        ita--;
        return zero(D - (B - ita->first));
    } 
    
    int next = ita->first;
    ita--;
    int prev = ita->first;    
    return zero(D - (next - A)) + zero(D - (B - prev));
}

int main() {
    std::ios::sync_with_stdio(false);
    int test; cin >> test;

    int N, D;
    while(cin >> N >> D) {
        X.clear();
        int A, B;
        for(int i=0; i<N; i++) {
            int value; cin >> value;
            X[value]++;
            int answer;
            if (i == 0) {
                A = B = value;
                answer = 0;
                //cout << " first" << endl;
            } else if (i == 1) {
                A = min(A, value);
                B = max(B, value);
                answer = zero(D - (B-A));
                //cout << " second " << answer << endl;
            } else {
                A = min(A, value);
                B = max(B, value);
               
                if (--X[A] == 0) X.erase(A);
                if (--X[B] == 0) X.erase(B);

                if (B-D-1 <= A+D+1) {
                    map<int, int>::iterator ita = X.lower_bound(B-D+1);
                    map<int, int>::iterator itb = X.upper_bound(A+D-1);
                    answer = 2000000000;
                    if (ita == itb) answer = 0;
                           
                    cout << setw(4) << A;         
                    for(map<int, int>::iterator it = ita; it != itb; it++) {
                        cout << setw(4) << it->first;
                    }                
                    cout << setw(4) << B << endl;
                    
                    cout << "  " << setw(4) << cost(D, A, B, ita->first);
                    answer = min(answer, cost(D, A, B, ita->first));
                    for(map<int, int>::iterator it = ita; it != itb; it++) {
                        cout << setw(4) << cost(D, A, B, it->first+1);
                        answer = min(answer, cost(D, A, B, it->first+1));
                    }
                    cout << endl << endl;
                } else {
                    answer = 0;
                }
                
                
                X[A]++;
                X[B]++;
            }
            
            //cout << (i > 0 ? " " : "") << answer;
        }
        cout << endl;
    }
    
}
