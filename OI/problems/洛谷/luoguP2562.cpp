#include <bits/stdc++.h>
using namespace std;
string str;
int isFull(string s) {
    int count_0 = 0;
    int count_1 = 0;
    for(char ch : s) {
        if(ch == '0') {
            count_0++;
        }
        if(ch == '1') {
            count_1++;
        }
    }
    if(count_0 == s.length()) {
        return 0;
    }
    else if(count_1 == s.length()) {
        return 1;
    }
    else {
        return -1;
    }
}
string func(string s) {
    if(isFull(s) == 0) {
        return "A";
    }
    if(isFull(s) == 1) {
        return "B";
    }
    int len = s.length();
    string s1 = s.substr(0, len / 2);
    string s2 = s.substr(len / 2, len / 2);
    return "C" + func(s1) + func(s2); 
}
void solve() {
    cin >> str;
    cout << func(str);
}
int main() {
    solve();
    return 0;
}