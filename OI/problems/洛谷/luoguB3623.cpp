#include <bits/stdc++.h>
using namespace std;
int n, k;
int temp[15];
bool isselect[15] = {false};
void dfs(int index) {
    if(index > k) {
        for(int i = 1; i <= k; i++) {
            cout << temp[i] << " ";
        }
        cout << endl;
        return;
    }
    for(int i = 1; i <= n; i++) {
        if(isselect[i]) {
            continue;
        }
        else {
            temp[index] = i;
            isselect[i] = true;
            dfs(index + 1); 
            isselect[i] = false;           
        }        

    }
}
void solve() {
    cin >> n >> k;
    dfs(1);
}
int main() {
    solve();
    return 0;
}