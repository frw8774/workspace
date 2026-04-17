#include <bits/stdc++.h>
using namespace std;
void solve() {
    string str;
    cin >> str;
    if(islower(str[0])) {
        str[0] = toupper(str[0]);
        cout << str[0];
    }
    else {
        cout << str[0];
    }
    for(int i = 1; i < str.size() - 1; i++) {
        if(i != 0 && isupper(str[i]) && str[i - 1] != '.') {
            cout << "." << str[i];
        }
        else if(i != 0 && str[i] == '.') {
            cout << str[i];
            if(!isupper(str[i + 1])) {
                str[i + 1] = toupper(str[i + 1]);
            }
        }
        else {
            cout << str[i];
        }
    }
    if(str[str.size() -1] != '.') {
        cout << str[str.size() - 1] << "." << endl;
    }
    else {
        cout << str[str.size() - 1] << endl;
    }
}
int main() {
    solve();
    return 0;
}