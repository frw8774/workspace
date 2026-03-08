#include <bits/stdc++.h>
using namespace std;
int n;
void solve() {
    cin >> n;
    int a[n + 1][n + 1];
    for(int i = 1; i < n; i++) {
        for(int j = i + 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    int dp[n + 1];
    dp[1] = 0;
    dp[2] = a[1][2];
    for(int i = 3; i <= n; i++) {
        int min_value = dp[1] + a[1][i];
        for(int j = 2; j < i; j++) {
            if(min_value > dp[j] + a[j][i]) {
                min_value = dp[j] + a[j][i];
            }
        }
        dp[i] = min_value;
    }
    cout << dp[n] << endl;
}
int main() {
    solve();
    return 0;
}