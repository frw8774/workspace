#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    cin >> s;
    string _s = s;
    int len = _s.length();
    reverse(s.begin(), s.end());
    for(int i = 0; i < len; i++) {
        string substr;
        if(i % 2 == 0) {
            substr = _s.substr(0, len - i);
        }
        else if(i % 2 == 1) {
            substr = s.substr(0, len - i);
        }
        cout << substr;
    }
    printf("\n");
    return 0;
}