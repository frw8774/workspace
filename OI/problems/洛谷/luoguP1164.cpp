#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N, M;
vector<int>price;
// int dp(int m, int num) {
//     if(m = 0) {
//         return 1;
//     }
//     if(m < 0 || num == 0) {
//         return 0;
//     }
//     if(m < price[num]) {
//         return dp(m, num - 1);
//     }
//     return dp(m, num - 1) + dp(m - price[num], num - 1);
// }
void solve() {
    cin >> N >> M;
    price.resize(N + 1);
    for(int i = 1; i <= N; i++) {
        cin >> price[i];
    }
    int dp[M + 1][N + 1];
    for(int i = 0; i <= M; i++) {
        for(int j = 0; j <= N; j++) {
            if(i == 0) {
                dp[i][j] = 1;
            }
            else {
                dp[i][j] = 0;
            }
        }
    }
    for(int j = 1; j <= N; j++) {
        for(int i = 1; i <= M; i++) {
            if(i < price[j]) {
                dp[i][j] = dp[i][j - 1];
            }
            else {
                dp[i][j] = dp[i][j - 1] + dp[i - price[j]][j - 1];
            }
        }
    }
    cout << dp[M][N] << endl;
}
int main() {
    solve();
    return 0;
}