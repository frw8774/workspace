#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n;
    cin >> n;
    int a[n + 5];
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int max_score = a[1];
    int max_pos = 1;
    for(int i = 2; i <= n; i++) {
        if(max_score < a[i]) {
            max_score = a[i];
            max_pos = i;
        }
    }
    if(a[1] > a[n]) {
        int temp = a[1];
        a[1] = a[n];
        a[n] = temp;
    }
    else {
        if(max_pos != n) {
            int temp = a[max_pos];
            a[max_pos] = a[n];
            a[n] = temp;
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}
int main() {
    solve();
    return 0;
}