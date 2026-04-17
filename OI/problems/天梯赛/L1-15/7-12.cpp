#include <bits/stdc++.h>
using namespace std;
int N;
char ch;
void solve() {
    cin >> N >> ch;
    int r, c = N;
    if(N % 2 == 1) {
        r = N / 2 + 1;
    }
    else {
        r = N / 2;
    }
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            if(i != r - 1 && j == c - 1) {
                cout << ch << endl;
            }
            else {
               cout << ch; 
            }
        }
    }
}
int main() {
    solve();
    return 0;
}