#include <bits/stdc++.h>
using namespace std;
int n, m, q;
void solve() {
    cin >> n >> m >> q;
    int a[n + 5][m + 5] = {0};
    for(int i = 1; i <= n; i++) {
        cin >> a[i][0];
    }
    for(int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        a[x][i] = y;
        for(int j = 1; j <= n; j++) {
            if(a[j][i] == 0) {
                a[j][i] = a[j][i - 1];
            }
        }
    }
    for(int i = 1; i <= q; i++) {
        int u, v;
        cin >> u >> v;
        cout << a[v][u - 1] << endl;
    }
}
int main() {
    solve();
    return 0;
}