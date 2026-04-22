#include <bits/stdc++.h>
using namespace std;
int N;
char ch;
string str;
void solve() {
    cin >> N >> ch;
    cin.ignore();
    getline(cin, str);
    int size = str.size();
    if(size <= N) {
        string _str(N - size, ch);
        cout << _str + str;
    }
    else {
        string _str = str.substr(size - N);
        cout << _str;
    }
}
int main() {
    solve();
    return 0;
}