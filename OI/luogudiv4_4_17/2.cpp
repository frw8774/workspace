#include <bits/stdc++.h>
using namespace std;
void solve() {
    int a, b;
    cin >> a >> b;
    if(a >= 8 && b <= 12) {
        cout << "M" << endl;
    }
    else if(a >= 13 && b <= 17) {
        cout << "A" << endl;
    }
    else if(a >= 18 && b <= 21) {
        cout << "E" << endl;
    }
    else {
        cout << "F" << endl;
    }
}
int main() {
    solve();
    return 0;
}