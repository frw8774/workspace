#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a, b, p;
ll quick_pow(ll n, ll m, ll x) {
    ll res = 1;
    while(m) {
        if(m & 1) {
            res *= n;
            res %= x;
        }
        m >>= 1;
        n = (n * n) % x;  
    }
    return res;
}
void solve() {
    cin >> a >> b >> p;
    cout << a << "^" << b << " mod " << p << "=" << quick_pow(a, b, p);
}
int main() {
    solve();
    return 0;
}