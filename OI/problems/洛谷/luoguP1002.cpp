#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, x_horse, y_horse;
ll mem[21][21]; //创建缓存数组来记忆化递归
bool isBlock[21][21]; //创建数组来确认控制点
ll func(int x, int y) {
    if(x < 0 || y < 0) { //在（0，0）以外的点无法到达，即有0条路径可到达
        return 0;
    }
    if(isBlock[x][y]) { //控制点也不可到达
        return 0;
    }
    if(x == 0 && y == 0) { //由于起点即为（0，0），故其到达自身只有1条路
        return 1;
    }
    if(mem[x][y] != -1) { //记忆化，抽取记忆的值
        return mem[x][y];
    }
    return mem[x][y] = func(x - 1, y) + func(x, y - 1); //记忆化递归
}
void solve() {
    ll del = 0;
    cin >> n >> m >> x_horse >> y_horse;
    memset(mem, -1, sizeof(mem)); //初始化缓存数组的值，使之均为1
    memset(isBlock, false, sizeof(isBlock)); //一开始所有的点都不是控制点
    vector<pair<int, int>> h_point = {{0, 0}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}}; //马的九个控制点的位移
    for(pair<int, int> p : h_point) {
        int x = x_horse + p.first;
        int y = y_horse + p.second;
        if(x >= 0 && x <= n && y >= 0 && y <= m) {
            isBlock[x][y] = true;
        }
    } //整个循环来确定在棋盘范围内的控制点
    cout << func(n, m); //输出结果
}
int main() {
    solve();
    return 0;
}