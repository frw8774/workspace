#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
void solve() {
    int n, c, k;
    cin >> n >> c >> k;
    int a[n];
    bool flag[n] = {false};
    bool _flag = false;
    int cnt = 0;
    ll final = c;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    for(int i = 0; i < n; i++) {
        if(a[i] <= final) {
            if(k - (final - a[i]) >= 0) {
                k -= final - a[i];
                final *= 2;
            }
            else {
                final += a[i] + k;
                k = 0;
            }
        }
    }
    cout << final << endl;
}
int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}