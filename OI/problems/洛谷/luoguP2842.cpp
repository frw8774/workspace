#include <bits/stdc++.h>
using namespace std;
int n, w;
const int INF = 1000000;
void solve() {
    cin >> n >> w;
    int a[n + 1];
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int dp[n + 1][w + 1];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 0;
    for(int i = 1; i <= w; i++) {
        dp[0][i] = INF;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= w; j++) {
            dp[i][j] = dp[i - 1][j];
            if(a[i] <= j) {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - a[i]] + 1);
                
            }
        }
    }
    cout << dp[n][w] << endl;
}
int main() {
    solve();
    return 0;
}