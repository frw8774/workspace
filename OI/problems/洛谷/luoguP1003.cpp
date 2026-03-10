#include <bits/stdc++.h>
using namespace std;
typedef struct {
    int x;
    int y;
    int x_len;
    int y_len;
} carpet;
int n;
void solve() {
    cin >> n;
    carpet c[n + 1];
    for(int i = 1; i <= n; i++) {
        cin >> c[i].x >> c[i].y >> c[i].x_len >> c[i].y_len;
    }
    int p_x, p_y;
    cin >> p_x >> p_y;
    int num = -1;
    for(int i = 1; i <= n; i++) {
        if((p_x >= c[i].x) && (p_x <= (c[i].x + c[i].x_len)) && (p_y >= c[i].y) && (p_y <= c[i].y + c[i].y_len)) {
            num = i;
        }
    }
    cout << num << endl;
}
int main() {
    solve();
    return 0;
}