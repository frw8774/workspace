/*
f[i]记录以a[i]为结尾的最长上升子序列的长度
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 5005;
int n;
int a[N], f[N];
void solve() {
    int ans = 1;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        f[i] = 1;
    }
    for(int i = 2; i <= n; i++) {
        for(int j = 1; j < i; j++) {
            if(a[j] < a[i]) {
                f[i] = max(f[j] + 1, f[i]);
            }
        }
        ans = max(ans, f[i]);
    }
    cout << ans << endl;
}
int main() {
    solve();
    return 0;
}
