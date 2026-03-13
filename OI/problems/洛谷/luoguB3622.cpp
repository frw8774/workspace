#include <bits/stdc++.h>
using namespace std;
int n;
char ch[15];
void dfs(int index) {
    if(index > n) {
        for(int i = 1; i <= n; i++) {
            cout << ch[i];
        }
        cout << endl;
        return;
    }
    for(int i = 1; i <= 2; i++) {
        if(i % 2 == 0) {
            ch[index] = 'Y';
        }
        else {
            ch[index] = 'N';
        }
        dfs(index + 1);
    }
}
void solve() {
    cin >> n;
    dfs(1);
}
int main() {
    solve();
    return 0;
}