/**
 * 回溯法解决八皇后问题
 * 题目来源：洛谷P1219
 * 
 * 输入格式：
 * 一行一个正整数n，表示棋盘是n*n大小的
 * 
 * 输出格式：
 * 前三行为前三个解，每个解的两个数字之间用一个空格隔开
 * 第四行只有一个数字，表示接的总数
 * 解的格式是输出的第i个数字num表示第i行第num列有一个棋子
 */
#include <bits/stdc++.h>
using namespace std;
int n;
int ans_num = 0;
vector<int> res;
vector<vector<int>> ans;
bool func(int num, int now) {
    for(int i = 0; i < res.size(); i++) {
        if(abs(i + 1 - num) == abs(res[i] - now)) {
            return false;
        }
    }
    return true;
}
void dfs(int num, bool* flag) {
    if(num > n) {
        ans_num++;
        ans.push_back(res);
        return;
    }
    else {
        for(int i = 1; i <= n; i++) {
            if(num == 1 || (func(num, i) && (flag[i] == false))) {
                res.push_back(i);
                flag[i] = true;
                dfs(num + 1, flag);
                res.pop_back();
                flag[i] = false;
            } 
        }
    }
}
int main() {
    cin >> n;
    bool* flag = (bool*)malloc(sizeof(bool) * (n + 1));
    for(int i = 1; i <= n; i++) {
        flag[i] = false;
    }
    dfs(1, flag);
    for(int i = 0; i < 3; i++) {
        for(int j : ans[i]) {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << ans_num << endl;
    return 0;
}