#include <bits/stdc++.h>
using namespace std;
int n;
vector<vector<int>> tree;
set<int> du;
int _du[100005] = {0};
int cnt = 0;
void func(int num) {
    cnt++;
    if(cnt != n) {
        cout << num << " ";
    }
    else {
        cout << num;
    }
    if(tree[num].size() == 0) {
        return; 
    }
    for(int i : tree[num]) {
        func(i);
    }
}
void solve() {
    cin >> n;
    tree.resize(n + 5);
    int root;
    for(int i = 1; i <= n; i++) {
        int fa;
        cin >> fa;
        if(fa == 0) {
            root = i;
        }
        tree[fa].push_back(i);
        _du[fa]++;
    }
    for(int i = 1; i <= n; i++) {
        sort(tree[i].begin(), tree[i].end());
    }
    for(int i = 1; i <= n; i++) {
        int num = tree[i].size();
        if(num == 0) {
            continue;
        }
        du.insert(num);
    }
    if(du.empty()) {
        cout << "0 yes" << endl;
    }
    else if(du.size() == 1) {
        cout << *du.begin() << " yes" << endl;
    }
    else {
        int max = *du.begin();
        for(int num : du) {
            if(num > max) {
                max = num;
            }
        }
        cout << max << " no" << endl;
    }
    func(root);
}
int main() {
    solve();
    return 0;
}