#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n;
    cin >> n;
    for(int i = n; i >= 1; i--) {
        cout << i << " ";
    }
    cout << endl;
}
int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}