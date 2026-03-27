#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n, m, x, y;
    int ans = 0;
    cin >> n >> m >> x >> y;
    int arr[n + 1][m + 1];
    int col[n + 1] = {0};
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> arr[i][j];
            if(arr[i][j] == 1) {
                col[i]++;
            }
        }
    }
    for(int i = n; i >= 1; i--) {
        if(i == x) {
            break;
        }
        else if(i > x) {
            ans += col[i];
        }
    }
    cout << ans + 1 << " " << ans + col[x];
}
int main() {
    solve();
    return 0;
}