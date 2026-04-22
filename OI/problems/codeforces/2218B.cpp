#include <bits/stdc++.h>
using namespace std;
void solve() {
    int a[7];
    int sum = 0;
    for(int i = 0; i < 7; i++) {
        cin >> a[i];
    }
    sort(a, a + 7);
    for(int i = 0; i < 6; i++) {
        sum -= a[i];
    }
    cout << sum + a[6] << endl;
}
int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}