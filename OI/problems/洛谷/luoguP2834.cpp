#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e9 + 7;
int n, w;
void solve() {
    cin >> n >> w;
    int a[n + 1];
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll dp[n + 1][w + 1];
    memset(dp, 0, sizeof(dp));
    for(int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= w; j++) {
            if(j < a[i]) {
                dp[i][j] = dp[i - 1][j];
            }
            else {
                dp[i][j] = (dp[i - 1][j] + dp[i][j - a[i]]) % N; 
            }
        }
    }
    cout << dp[n][w] << endl;
}
int main() {
    solve();
    return 0;
}