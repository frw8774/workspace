#include <bits/stdc++.h>
using namespace std;
string a, b;
void solve() {
    getline(cin, a);
    getline(cin, b);
    int N = a.length();
    bool flag[N] = {false};
    for(int i = 0; i < N; i++) {
        if(b.find(a[i]) != string::npos) {
            flag[i] = true;
        }
    }
    for(int i = 0; i < N; i++) {
        if(flag[i]) {
            continue;
        }
        else {
            cout << a[i];
        }
    }
}
int main() {
    solve();
    return 0;
}