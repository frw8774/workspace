#include <bits/stdc++.h>
using namespace std;
int N;
char ch;
void func() {
    int cnt = 1, _i = 3, num = 1;
    while(true) {
        if((cnt + _i * 2) > N) {
            break;
        }
        cnt += _i * 2;
        _i += 2;
        num++;
    }
    int more = N - cnt;
    _i -= 2;
    for(int i = _i; i >= 1; i -= 2) {
        for(int j = 1; j <= (_i - i) / 2; j++) {
            cout << " ";
        }
        for(int j = 1; j <= i; j++) {
            cout << ch;
        }
        cout << endl;
    }
    for(int i = 3; i <= _i; i += 2) {
        for(int j = 1; j <= (_i - i) / 2; j++) {
            cout << " ";
        }
        for(int j = 1; j <= i; j++) {
            cout << ch;
        }
        cout << endl;
    }
    cout << more << endl;
}
void solve() {
    cin >> N >> ch;
    func();
}
int main() {
    solve();
    return 0;
}