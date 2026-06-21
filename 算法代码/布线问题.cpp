/**
 * 布线问题的问题描述：
 * 有一个n*n的方阵，给出起点a的位置x_a,y_a，以及终点b的位置x_b,y_b，求a到b的最短路径长度，方阵中某些方格不能走，会给出坐标
 * 
 * 输入描述:
 * 第一行输入一个整数n表示区域大小
 * 第二行输入起点a的位置和终点b的位置
 * 第三行输入一个数m表示有m个点不能布线
 * 接下来m行每行两个数字x,y表示不能布线的点坐标
 * 
 * 输出描述：
 * 输出第一行为一个整数，表示从a到b的最短路径长度
 * 往后若干行为从a到b的最短路径经过的坐标，每行两个整数，分别为点的x坐标和y坐标
 */
#include <bits/stdc++.h>
using namespace std;
const int max_limit = 1e9;
int n;
int x_a, y_a, x_b, y_b;
bool isvalid(pair<int, int> p, int** matrix) {
    if(p.first >= 0 && p.first < n && p.second >= 0 && p.second < n) {
        if(matrix[p.first][p.second] != -1) {
            return true;
        }
    }
    return false;
}
void bfs(int** matrix) {
    queue<pair<int, int>> q;
    pair<int, int> p;
    p.first = x_a;
    p.second = y_a;
    q.push(p);
    while(!q.empty()) {
        p = q.front();
        q.pop();
        for(int i = 0; i < 4; i++) {
            pair<int, int> _p;
            if(i == 0) {
                _p.first = p.first - 1;
                _p.second = p.second;
            }
            else if(i == 1) {
                _p.first = p.first;
                _p.second = p.second - 1;
            }
            else if(i == 2) {
                _p.first = p.first + 1;
                _p.second = p.second;
            }
            else if(i == 3) {
                _p.first = p.first;
                _p.second = p.second + 1;
            }
            if(isvalid(_p, matrix)) {
                q.push(_p);
                matrix[_p.first][_p.second] = min(matrix[_p.first][_p.second], matrix[p.first][p.second] + 1);
                if(_p.first == x_b && _p.second == y_b) {
                    cout << matrix[x_b][y_b] << endl;
                    return;
                }
            }
        }
    }
}
void getAns(int x, int y, int** matrix) { 
    if(x == x_a && y == y_a) {
        cout << "(" << x << ", " << y << ")" << endl;
        return;
    }
    int _x, _y;
    for(int i = 0; i < 4; i++) {
        if(i == 0) {
            _x = x - 1;
            _y = y;
        }
        else if(i == 1) {
            _x = x;
            _y = y - 1;
        }
        else if(i == 2) {
            _x = x + 1;
            _y = y;
        }
        else if(i == 3) {
            _x = x;
            _y = y + 1;
        }
        pair<int, int> temp;
        temp.first = _x;
        temp.second = _y;
        if(isvalid(temp, matrix) && matrix[_x][_y] == matrix[x][y] - 1) {
            break;
        }
    }
    getAns(_x, _y, matrix);
    cout << "(" << x << ", " << y << ")" << endl;
}
int main() {
    cin >> n;
    int** matrix = (int**)malloc(sizeof(int*) * n);
    for(int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(sizeof(int) * n);
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            matrix[i][j] = max_limit;
        }
    }
    cin >> x_a >> y_a >> x_b >> y_b;
    matrix[x_a][y_a] = 0;
    int m;
    cin >> m;
    for(int i = 0; i < m; i++) {
        int x,y;
        cin >> x >> y;
        matrix[x][y] = -1;
    }
    bfs(matrix);
    getAns(x_b, y_b, matrix);
    for(int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    return 0;
}
