#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N, M, Q;
void solve() {
    cin >> N >> M >> Q;
    bool flag_c[N + 1] = {false};
    bool flag_v[M + 1] = {false};
    ll cnt = N * M;
    int _col = 0;
    int _vol = 0;
    for(int i = 1; i <= Q; i++) {
        int T, C;
        cin >> T >> C;
        if(T == 0) {
            if(flag_c[C]) {
                continue;
            }
            cnt -= M - _vol;
            _col++;
            flag_c[C] = true;
        }
        if(T == 1) {
            if(flag_v[C]) {
                continue;
            }
            cnt -= N - _col;
            _vol++;
            flag_v[C] = true;
        }
    }
    cout << cnt << endl;
}
int main() {
    solve();
    return 0;
}