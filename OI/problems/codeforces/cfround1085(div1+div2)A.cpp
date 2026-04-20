#include <bits/stdc++.h>
using namespace std;
void func(string s) {
    int max_cnt = 0, min_cnt = 0;
    for(int i = 1; i < s.size() - 1; i++) {
        if(s[i - 1] == '1' && s[i + 1] == '1') {
            if(s[i] == '0') {
                s[i] = '1';
            }
        }
    }
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '1') {
            max_cnt++;
        }
    }
    for(int i = 1; i < s.size() - 1; i++) {
        if(s[i - 1] == '1' && s[i + 1] == '1') {
            if(s[i] == '1') {
                s[i] = '0';
            }
        }
    }
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '1') {
            min_cnt++;
        }
    }
    cout << min_cnt << " " << max_cnt << endl;
}
void solve() {
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) {
        int n;
        cin >> n;
        string str;
        cin >> str;
        func(str);
    }
}
int main() {
    solve();
    return 0;
}