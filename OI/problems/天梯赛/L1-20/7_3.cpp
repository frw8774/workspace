#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N;
void who_is(ll sa, ll sb) {
    int na = 0, nb = 0;
    ll temp_a = sa, temp_b = sb;
    while(temp_a) {
        na += (temp_a % 10);
        temp_a /= 10;
    }
    while(temp_b) {
        nb += (temp_b % 10);
        temp_b /= 10;
    }
    if(sa % nb == 0 && sb % na != 0) {
        cout << "A" << endl;
        return;
    }
    if(sb % na == 0 && sa % nb != 0) {
        cout << "B" << endl;
        return;
    }
    if((sa % nb != 0 && sb % na != 0) || (sa % nb == 0 && sb % na == 0)) {
        if(sa > sb) {
            cout << "A" << endl;
            return;
        }
        else {
            cout << "B" << endl;
            return;
        }
    }
}
void solve() {
    cin >> N;
    for(int i = 0; i < N; i++) {
        ll sa, sb;
        cin >> sa >> sb;
        who_is(sa, sb);
    }
}
int main() {
    solve();
    return 0;
}