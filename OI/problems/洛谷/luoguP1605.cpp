#include <bits/stdc++.h>
using namespace std;
int N, M, T;
int sx, sy, fx, fy;
int cnt = 0;
int dir_x[4] = {0, 1, 0, -1};
int dir_y[4] = {1, 0, -1, 0};
bool is_select[6][6] = {false};
void dfs(int x, int y) {
    if(x == fx && y == fy) {
        cnt++;
        return;
    }
    for(int i = 0; i < 4; i++) {
        int n_x = dir_x[i] + x;
        int n_y = dir_y[i] + y;
        if(n_x > N || n_x < 1 || n_y > M || n_y < 1) {
            continue;
        }
        if(is_select[n_x][n_y]) {
            continue;
        }
        is_select[n_x][n_y] = true;
        dfs(n_x, n_y);
        is_select[n_x][n_y] = false;
    }
}
void solve() {
    cin >> N >> M >> T;
    cin >> sx >> sy >> fx >> fy;
    for(int i = 0; i < T; i++) {
        int _x, _y;
        cin >> _x >> _y;
        is_select[_x][_y] = true;
    }
    is_select[sx][sy] = true;
    dfs(sx, sy);
    cout << cnt << endl;
}
int main() {
    solve();
    return 0;
}