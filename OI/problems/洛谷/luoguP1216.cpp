#include <bits/stdc++.h>
using namespace std;
int r;
void solve() {
    cin >> r;
    int a[r + 1][r + 1];
    memset(a, 0, sizeof(a));
    for(int i = 1; i <= r; i++) {
        for(int j = 1; j <= i; j++) {
            cin >> a[i][j];
        }
    }
    int dp[r + 1][r + 1];
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= r; i++) {
        dp[r][i] = a[r][i];
    }
    for(int i = r - 1; i >= 1; i--) {
        for(int j = 1; j <= i; j++) {
            dp[i][j] = max(dp[i + 1][j], dp[i + 1][j + 1]) + a[i][j];
        }
    }
    cout << dp[1][1] << endl;
}
int main() {
    solve();
    return 0;
}