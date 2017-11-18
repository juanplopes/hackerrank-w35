#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <set>
using namespace std;

struct Gap {
    int x, y;
    Gap(int x, int y) : x(x), y(y) { }
    
    inline bool operator <(const Gap& other) const {
        if (y-x != other.y-other.x) return y-x > other.y-other.x;
        return x < other.x;
    }
};

map<int, int> X;
set<Gap> G;

int zero(int v) {
    return v < 0 ? 0 : v;
}

void updateGap(int v) {
    if (X.find(v) != X.end()) return;
    
    map<int, int>::iterator ita = X.lower_bound(v);
    map<int, int>::iterator itb = X.upper_bound(v);

    if (itb == X.end()) {
        itb--;
        G.insert(Gap(itb->first, v));
        return;
    }
    
    if (ita == X.begin()) {
        G.insert(Gap(v, itb->first));
        return;
    }

    ita--;
    int first = ita->first;
    int second = itb->first;
    //cout << "          UP" << first << " " << second << endl;
    G.erase(Gap(first, second));
    G.insert(Gap(first, v));
    G.insert(Gap(v, second));
    
}

int main() {
    std::ios::sync_with_stdio(false);
    int test; cin >> test;

    int N, D;
    while(cin >> N >> D) {
        X.clear(); G.clear();
        int A, B;
        for(int i=0; i<N; i++) {
            int value; cin >> value;
         
            int answer;
            if (i == 0) {
                A = B = value;
                X[value]++;
                answer = 0;
                //cout << " first" << endl;
            } else if (i == 1) {
                A = min(A, value);
                B = max(B, value);
                G.insert(Gap(A, B));
                X[value]++;
                answer = zero(D - (B-A));
                //cout << " second " << answer << endl;
            } else {
                A = min(A, value);
                B = max(B, value);
                
                int XA = B - D;
                int XB = A + D;
                
                updateGap(value);
                X[value]++;
                
                if (XA < XB) {
                    if (--X[A] == 0) X.erase(A);
                    if (--X[B] == 0) X.erase(B);
                
                    map<int, int>::iterator ita = X.lower_bound(XA+1);
                    map<int, int>::iterator itb = X.upper_bound(XB-1);
                    
                    if (ita != itb) {
                        answer = 2000000000;
                        int first = ita->first;
                        itb--;
                        int last = itb->first;
                        answer = min(answer, zero(D - (B-last)));
                        answer = min(answer, zero(D - (first-A)));
                        
                        int gap = -1;                        
                        for(set<Gap>::iterator it = G.begin(); it != G.end(); it++) {
                            //cout << "   " << it->x << " " << it->y << endl;
                            if (it->x > XA and it->y < XB) {
                                gap = max(gap, it->y - it->x);
                                answer = min(answer, 2*D - (B-A) - gap);
                                break;
                            } else {
                                G.erase(it);
                                
                            }
                        }
                        //cout << " " << (D - (B-last)) << " " << (D - (first-A)) << " " << gap << " " << answer << endl;
                        
                    } else {
                        answer = 0;
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
