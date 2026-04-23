#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n, k;
    cin >> n >> k;
    int sum = 0, num;
    int c_sum = n * k;
    for(int i = 0; i < n; i++) {
        cin >> num;
        sum += num;
    }
    if(sum % 2 == 0 && c_sum % 2 == 1) {
        cout << "NO" << endl;
    }
    else {
        cout << "YES" << endl;
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