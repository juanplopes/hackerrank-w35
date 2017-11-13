#include <iostream>
#include <string>
using namespace std;

bool ok(int price) {
    int c7 = 0, c4 = 0, co = 0;
    while(price) {
        int v = price % 10;
        if (v == 7) c7++;
        else if (v == 4) c4++;
        else co++;
        
        price /= 10;
    }
    return co == 0 and c7 == c4;
}

int main() {
    int N;
    while(cin >> N) {
        string s; int price;
        string mins = "-1"; int minprice = 2000000000;
        for(int i=0; i<N; i++) {
            cin >> s >> price;
            if (ok(price) and price < minprice) {
                mins = s;
                minprice = price;
            }
        }
        cout << mins << endl;
    }
}
