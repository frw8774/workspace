#include <bits/stdc++.h>
using namespace std;
int n, m;
int temp[30];
void dfs(int index, int start) {
    if(index > m) {
        for(int i = 1; i <= m; i++) {
            cout << temp[i] << " ";
        }
        cout << endl;
        return;
    }
    for(int i = start; i <= n; i++) {
        temp[index] = i;
        dfs(index + 1, i + 1);
    }
}
void solve() {
    cin >> n >> m;
    dfs(1, 1);
}
int main() {
    solve();
    return 0;
}