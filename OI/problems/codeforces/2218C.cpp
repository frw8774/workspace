#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n;
    cin >> n;
    int len = n * 3;
    for(int i = 1; i <= n; i++) {
        cout << i << " " << len - (i - 1) * 2 << " " << len - (i - 1) * 2 - 1 << " ";
    }
}
int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}