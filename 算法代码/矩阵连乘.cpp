// #include <bits/stdc++.h>
// using namespace std;
// int N;
// int p[100000];
// typedef long long ll;
// void func() {
//     ll m[N + 1][N + 1];
//     for(int i = 1; i <= N; i++) {
//         m[i][i] = 0;
//     }
//     for(int i = 1; i < N; i++) {
//         for(int j = 1; j < N; j++) {
//             m[j][j + i] = m[j][j] + m[j + 1][j + i] + p[j - 1] * p[j] * p[j + i];
//             for(int k = j + 1; k < j + i; k++) {
//                 ll _new = m[j][k] + m[k + 1][j + i] + p[j - 1] * p[k] * p[j + i];
//                 if(m[j][j + i] > _new) {
//                     m[j][j + i] = _new;
//                 }
//             }
//         }
//     }
//     cout << m[1][N] << endl;
// }
// int main() {
//     cin >> N;
//     for(int i = 0; i <= N; i++) {
//         cin >> p[i];
//     }
//     func();
//     cout << endl;
//     return 0;
// }
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
vector<int> p;
vector<vector<ll>> m;    // m[i][j] Ai~Aj最小乘法次数
vector<vector<int>> s;    // s[i][j] Ai~Aj最优分割点k

void dp() {
    // 单个矩阵代价为0
    for (int i = 1; i <= N; i++)
        m[i][i] = 0;

    // len: 矩阵区间长度，从2个到N个
    for (int len = 2; len <= N; len++) {
        // j：区间起点
        for (int j = 1; j + len - 1 <= N; j++) {
            int r = j + len - 1; // 区间终点
            m[j][r] = 1e18;     // 初始无穷大
            // 枚举分割点k
            for (int k = j; k < r; k++) {
                ll cost = m[j][k] + m[k+1][r] + 1LL * p[j-1] * p[k] * p[r];
                if (cost < m[j][r]) {
                    m[j][r] = cost;
                    s[j][r] = k;
                }
            }
        }
    }
    cout << m[1][N] << "\n";
}

// 递归输出带括号表达式（标准输出格式）
void trace(int l, int r) {
    if (l == r) {
        cout << "A" << l;
        return;
    }
    int k = s[l][r];
    cout << "(";
    trace(l, k);
    trace(k+1, r);
    cout << ")";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N;
    p.resize(N+1);
    for (int i = 0; i <= N; i++)
        cin >> p[i];
    
    // 动态分配二维数组，下标1~N
    m.assign(N+1, vector<ll>(N+1, 0));
    s.assign(N+1, vector<int>(N+1, 0));
    
    dp();
    trace(1, N);
    cout << "\n";
    return 0;
}