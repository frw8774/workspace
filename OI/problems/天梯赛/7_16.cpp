#include <bits/stdc++.h>
using namespace std;
int N;
string str;
void solve() {
    cin >> N;
    cin.ignore();
    getline(cin, str);
    int size = str.size();
    if(size % N == 0) {
        int cnt = 0;
        int n = size / N;
        char ch[N][n];        
        memset(ch, 0, sizeof(ch));
        for(int i = n - 1; i >= 0; i--) {
            for(int j = 0; j < N; j++) {
                ch[j][i] = str[cnt];
                cnt++;
            }
        }
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < n; j++) {
                cout << ch[i][j];
            }
            cout << endl;
        }
    }
    else if(size % N != 0) {
        int cnt = 0;
        int n = size / N + 1;
        char ch[N][n];
        memset(ch, 0, sizeof(ch));
        for(int i = n - 1; i >= 0; i--) {
            for(int j = 0; j < N; j++) {
                if(cnt >= size) {
                    ch[j][i] = ' ';
                }
                else {
                    ch[j][i] = str[cnt];
                    cnt++;
                }
            }
        }
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < n; j++) {
                cout << ch[i][j];
            }
            cout << endl;
        }
    }
}
int main() {
    solve();
    return 0;
}