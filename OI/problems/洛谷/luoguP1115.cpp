#include <bits/stdc++.h>
using namespace std;
int n;
void solve() {
    cin >> n;
    int a[n + 1];
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int dp[n + 1];
    dp[1] = a[1];
    int max_value = dp[1];
    for(int i = 2; i <= n; i++) {
        dp[i] = max(dp[i - 1] + a[i], a[i]);
        if(max_value < dp[i]) {
            max_value = dp[i];
        }
    }
    cout << max_value << endl;
}
int main() {
    solve();
    return 0;
}