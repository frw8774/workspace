#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef struct {
    int l;
    int r;
} tree;
int n;
vector<tree> t;
queue<tree> q;
int depth = 0;
void bfs() {
    while(!q.empty()) {
        depth++;
        int size = q.size();
        for(int i = 0; i < size; i++) {
            tree temp = q.front();
            q.pop();
            if(temp.l != 0) {
                q.push(t[temp.l]);
            }
            if(temp.r != 0) {
                q.push(t[temp.r]);
            }
        }
    }
}
void solve() {
    cin >> n;
    t.resize(n + 5);
    for(int i = 1; i <= n; i++) {
        tree temp;
        cin >> temp.l >> temp.r;
        t[i] = temp;
    }
    q.push(t[1]);
    bfs();
    cout << depth << endl;
}
int main() {
    solve();
    return 0;
}