#include <bits/stdc++.h>
using namespace std;
int n, m;
typedef struct {
    int p;
    int v;
} thing;
void solve() {
    cin >> n >> m;
    thing t[m + 1];
    for(int i = 1; i <= m; i++) {
        cin >> t[i].v >> t[i].p;
    }
    int dp[m + 1][n + 1];
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(j < t[i].v) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - t[i].v] + (t[i].v) * (t[i].p));
            }
        }
    }
    cout << dp[m][n] << endl;
}
int main() {
    solve();
    return 0;
}