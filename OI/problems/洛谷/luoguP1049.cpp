#include <bits/stdc++.h>
using namespace std;
int V, n;
vector<int> vol;
void solve() {
    cin >> V >> n;
    vol.resize(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> vol[i];
    }
    int dp[n + 1][V + 1];
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= V; j++) {
            if(j < vol[i]) {
                dp[i][j] = dp[i - 1][j];
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - vol[i]] + vol[i]);
            }
        }
    }
    cout << V - dp[n][V] << endl;
}
int main() {
    solve();
    return 0;
}