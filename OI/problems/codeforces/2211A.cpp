#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n;
    cin >> n;
    int a[n];
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    if(n == 1) {
        cout << 1 << endl;
    }
    else if(n >= 2) {
        for(int i = 0; i < n; i++) {
            cout << 2 << " ";
        }
        cout << endl;
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