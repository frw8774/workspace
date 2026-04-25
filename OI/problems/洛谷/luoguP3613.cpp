#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n, q;
    cin >> n >> q;
    vector<map<int, int>> arr;
    arr.resize(n + 1);
    for(int i = 0; i < q; i++) {
        int op;
        cin >> op;
        if(op == 1) {
            int I, J, K;
            cin >> I >> J >> K;
            arr[I][J] = K;
        }
        else if(op == 2) {
            int I, J;
            cin >> I >> J;
            cout << arr[I][J] << endl;
        }
    }
}
int main() {
    solve();
    return 0;
}