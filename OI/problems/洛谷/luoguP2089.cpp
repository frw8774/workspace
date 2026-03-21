#include <bits/stdc++.h>
using namespace std;
int n;
vector<vector<int>> ans;
int num = 0;
vector<int> temp;
void dfs(int index, int remain) {
    if(index > 10) {
        if(remain == 0) {
            num++;
            ans.push_back(temp);
        }
        return;
    }
    for(int i = 1; i <= 3; i++) {
        if(remain - i < 0) {
            continue;
        }
        temp.push_back(i);
        dfs(index + 1, remain - i);
        temp.pop_back();
    }
}
void solve() {
    cin >> n;
    if(n > 30 || n < 10) {
        cout << 0 << endl;
        return;
    }
    else {
        dfs(1, n);
        cout << num << endl;
        for(int i = 0; i < ans.size(); i++) {
            for(int j : ans[i]) {
                cout << j << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}
int main() {
    solve();
    return 0;
}