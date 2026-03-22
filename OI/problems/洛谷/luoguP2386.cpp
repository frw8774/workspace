#include <bits/stdc++.h>
using namespace std;
int t;
int cnt = 0;
void dfs(int index, int remain, int last, int m, int n) {
    if(index > n) {
        if(remain == 0) {
            cnt++;
        }
        return;
    }
    for(int i = last; i <= remain; i++) {
        dfs(index + 1, remain - i, i, m, n);
    }
}
void solve() {
    cin >> t;
    for(int i = 0; i < t; i++) {
        int m, n;
        cin >> m >> n;
        if(n > m) {
            n = m;
        }
        dfs(1, m, 0, m, n);
        cout << cnt << endl;
        cnt = 0;
    }
}
int main() {
    solve();
    return 0;
}