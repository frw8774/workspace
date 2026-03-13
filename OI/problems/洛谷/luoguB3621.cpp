#include <bits/stdc++.h>
using namespace std;
int n, k;
int temp[10];
void dfs(int index) {
    if(index > n) {
        for(int i = 1; i <= n; i++) {
            cout << temp[i] << " ";
        }
        cout << endl;
        return;
    }
    for(int i = 1; i <= k; i++) {
        temp[index] = i;
        dfs(index + 1);
    }
}
void solve() {
    cin >> n >> k;
    dfs(1);
}
int main() {
    solve();
    return 0;
}