#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int m;
set<ll> a;
void solve() {
    cin >> m;
    for(int i = 0; i < m; i++) {
        int op;
        ll _length;
        cin >> op >> _length;
        if(op == 1) {
            if(a.count(_length) == true) {
                cout << "Already Exist" << endl;
            }
            else {
                a.insert(_length);
            }
        }
        if(op == 2) {
            if(a.size() == 0) {
                cout << "Empty" << endl;
            }
            else {
                auto it = a.find(_length);
                if(it != a.end()) {
                    cout << _length << endl;
                    a.erase(it);
                }
                else {
                    ll ans = -1;
                    ll prev = -1;
                    ll next = -1;
                    auto it1 = a.lower_bound(_length);
                    auto it2 = a.upper_bound(_length);
                    if(it1 != a.begin()) {
                        prev = *(--it1);
                    }
                    if(it2 != a.end()) {
                        next = *it2;
                    }
                    if(prev == -1) {
                        ans = next;
                    }
                    else if(next == -1) {
                        ans = prev;
                    }
                    else {
                        ll dis_prev = _length - prev;
                        ll dis_next = next - _length;
                        if(dis_prev <= dis_next) {
                            ans = prev;
                        }
                        else {
                            ans = next;
                        }
                    }
                    cout << ans << endl;
                    a.erase(ans);
                }
            }
        }
    }
}
int main() {
    solve();
    return 0;
}