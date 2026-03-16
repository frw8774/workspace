#include <bits/stdc++.h>
using namespace std;
int T;
int func(string s) {
    int ans1 = 0;
    int ans2 = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == 'A' && i % 2 == 1) {
            ans1++;
        }
        if(s[i] == 'A' && i % 2 == 0) {
            ans2++;
        }
    }
    return min(ans1, ans2);
}
void solve() {
    cin >> T;
    for(int i = 1; i <= T; i++) {
        int n;
        string str;
        cin >> n >> str;
        cout << func(str) << endl;
    }
}
int main() {
    solve();
    return 0;
}