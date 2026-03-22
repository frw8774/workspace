#include <bits/stdc++.h>
using namespace std;
typedef struct {
    int l;
    int r;
    int id;
} tree;
vector<tree> t; 
vector<int> pre;
vector<int> mid;
vector<int> back;
int n;
void pre_func(int u) { 
    if (u == 0) return; 
    pre.push_back(u);
    pre_func(t[u].l);
    pre_func(t[u].r);
}
void mid_func(int u) {
    if (u == 0) return;
    mid_func(t[u].l);
    mid.push_back(u);
    mid_func(t[u].r);
}
void back_func(int u) {
    if (u == 0) return;
    back_func(t[u].l);
    back_func(t[u].r);
    back.push_back(u);
}
void solve() {
    cin >> n;
    t.resize(n + 5);
    for(int i = 1; i <= n; i++) {
        cin >> t[i].l >> t[i].r; 
        t[i].id = i;
    }
    pre_func(1);
    mid_func(1);
    back_func(1);
    for(int i : pre) {
        cout << i << " ";
    }
    cout << endl;
    for(int i : mid) {
        cout << i << " ";
    }
    cout << endl;
    for(int i : back) {
        cout << i << " ";
    }
}
int main() {
    solve();
    return 0;
}