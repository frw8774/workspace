#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int S;
ll sum[2005];
void func() {
    memset(sum, 0, sizeof(sum));
    for(int i = 1; i < 2005; i++) {
        for(int j = 2 * i; j < 2005; j += i) {
            sum[j] += i;
        }
    }
}
void solve() {
    cin >> S;
    ll dp[S + 1][S + 1];
    func();
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= S; i++) {
        for(int j = 1; j <= S; j++) {
            if(j < i) {
                dp[i][j] = dp[i - 1][j];
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - i] + sum[i]);
            }
        }
    }
    cout << dp[S][S] << endl;
}
int main() {
    solve();
    return 0;
}