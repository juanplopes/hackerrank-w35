#include <iostream>
#include <string>
#include <cmath>
#include <map>
using namespace std;

map<int, int> X;

int zero(int v) {
    return v < 0 ? 0 : v;
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
                
                int XA = B - D;
                int XB = A + D;
                
                if (XA < XB) {
                    if (--X[A] == 0) X.erase(A);
                    if (--X[B] == 0) X.erase(B);
                
                    map<int, int>::iterator ita = X.lower_bound(XA+1);
                    map<int, int>::iterator itb = X.upper_bound(XB-1);
                    
                    if (ita != itb) {
//                        cout << " ????" << i << " " << XA << " " << XB << endl;
                        answer = 2000000000;
                        int prev = ita->first;
                        answer = min(answer, zero(D - (prev - A)));
                        for(ita++ ;ita!=itb; ita++) {
                            int next = ita->first;
                            answer = min(answer, zero(D - (next - A)) + zero(D - (B - prev)));
//                            cout << " > " << A << " " << prev << " " << next << " " << B << " " << answer << endl;
                            prev = next;
                        }
                        answer = min(answer, zero(D - (B - prev)));
//                        cout << " !!!!" << i << " " << XA << " " << XB << " " << answer << endl;
                        //cout << " other " << XA << " " << XB << " " << minn << " " << maxx << " " << answer << endl;
                    } else {
                        answer = 0;
                      //  cout << " zero " << XA << " " << XB << " " << answer << endl;
                    }
                    
                    X[A]++;
                    X[B]++;
                } else {
                    answer = 0;
                    //cout << " less " << XA << " " << XB << " " << answer << endl;
                }
            }
            
            cout << (i > 0 ? " " : "") << answer;
        }
        cout << endl;
    }
    
}
