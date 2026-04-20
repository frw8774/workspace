#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n;
    cin >> n;
    int arr[n * n + 5] = {0};
    for(int i = 1; i <= n * n; i++) {
        int num;
        cin >> num;
        arr[num]++;
    }
    for(int i : arr) {
        if(i > n * n - n) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
}
int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) {
        solve();
    }
    return 0;
} 