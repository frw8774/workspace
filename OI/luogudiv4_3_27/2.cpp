#include <bits/stdc++.h>
using namespace std;
void solve() {
    int a, b;
    cin >> a >> b;
    if(b == 1) {
        if(a < 4) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
    else if(b == 0) {
        cout << "No" << endl;
    }
}
int main() {
    solve();
    return 0;
}