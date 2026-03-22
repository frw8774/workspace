#include <bits/stdc++.h>
using namespace std;
int n;
vector<vector<int>> ans;
vector<int> temp;
void dfs(int remain, int last) {
    if(remain == 0) {
        ans.push_back(temp);
        return;
    }
    for(int i = last; i <= n - 1; i++) {
        if(remain - i < 0) {
            continue;
        }
        temp.push_back(i);
        dfs(remain - i, i);
        temp.pop_back();
    }
}
void solve() {
    cin >> n;
    dfs(n, 1);
    for(vector<int> a : ans) {
        for(int i = 0; i < a.size() - 1; i++) {
            cout << a[i] << "+";
        }
        cout << a[a.size() - 1] << endl;
    }
}
int main() {
    solve();
    return 0;
}