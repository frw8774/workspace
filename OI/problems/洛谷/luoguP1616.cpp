#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int t, m;
void solve() {
    cin >> t >> m;
    int a[m + 1], b[m + 1];
    for(int i = 1; i <= m; i++) {
        cin >> a[i] >> b[i];
    }
    ll dp[t + 1];
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= m; i++) {
        for(int j = a[i]; j <= t; j++) {
            dp[j] = max(dp[j], dp[j - a[i]] + b[i]);
        }
    }
    cout << dp[t] << endl;
}
int main() {
    solve();
    return 0;
}