#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void e_solve() {
    vector<ll> prim; 
    bool flag[1000] = {false};
    for(ll i = 2; i < 1000; i++) {
        if(flag[i] == false) {
            prim.push_back(i);
        }
        for(ll j = i * 2; j < 1000; j += i) {
            flag[j] = true;
        }
    }
}
void E_solve() {
    vector<ll> prim;
    bool flag[1000] = {false};
    for(int i = 2; i < 1000; i++) {
        if(flag[i] == false) {
            prim.push_back(i);
        }
        for(int j = 0; i * prim[j] < 1000; j++) {
            flag[i * prim[j]] = true;
            if(i % prim[j] == 0) {
                break;
            }
        }
    }
    for(int i : prim) {
        cout << i << endl;
    }
}
int main() {
    // e_solve();
    E_solve();
    return 0;
}