/*
未优化，采用递归写法，会TLE
可以将递归改成递推，采用循环来写
#include <bits/stdc++.h>
using namespace std;
int T, M;
int mem[1005][105];
vector<int>value;
vector<int>need_time;
int dp(int t, int i) {
    if(i <= 0 || t <= 0) {
        return 0;
    }
    if(mem[t][i] != -1) {
        return mem[t][i];
    }
    if(t < need_time[i]) {
        return dp(t, i - 1);
    }
    return max(dp(t, i - 1), dp(t - need_time[i], i - 1) + value[i]);
}
void solve() {
    memset(mem, -1, sizeof(mem));
    cin >> T >> M;
    value.resize(M + 1);
    need_time.resize(M + 1);
    for(int i = 1; i <= M; i++) {
        cin >> need_time[i] >> value[i];
    }
    cout << dp(T, M) << endl;
}
int main() {
    solve();
    return 0;
}
*/

/*递推写法
#include <bits/stdc++.h>
using namespace std;
int T, M;
vector<int>value;
vector<int>need_time;
void solve() {
    cin >> T >> M;
    value.resize(M + 1);
    need_time.resize(M + 1);
    for(int i = 1; i <= M; i++) {
        cin >> need_time[i] >> value[i];
    }
    int dp[T + 1][M + 1];
    for(int i = 0; i < T + 1; i++) {
        for(int j = 0; j < M + 1; j++) {
            dp[i][j] = 0;
        }
    }
    for(int j = 1; j <= M; j++) {
        for(int i = 0; i <= T; i++) {
            if(i < need_time[j]) {
                dp[i][j] = dp[i][j - 1];
            }
            else {
                dp[i][j] = max(dp[i][j - 1], dp[i - need_time[j]][j - 1] + value[j]);
            }
        }
    }
    cout << dp[T][M] << endl;
}
int main() {
    solve();
    return 0;
}
*/

//再次优化成一维数组
#include <bits/stdc++.h>
using namespace std;
int T, M;
void solve() {
    cin >> T >> M;
    vector<int>need_time(M + 1);
    vector<int>value(M + 1);
    for(int i = 1; i <= M; i++) {
        cin >> need_time[i] >> value[i];
    }
    vector<int>dp(T + 1, 0);
    for(int j = 1; j <= M; j++) {
        for(int i = T; i >= need_time[j]; i--) {
            dp[i] = max(dp[i], dp[i - need_time[j]] + value[j]);
        }
    }
    cout << dp[T] << endl;
}
int main() {
    solve();
    return 0;
}