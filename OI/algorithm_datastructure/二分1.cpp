#include <bits/stdc++.h>
using namespace std;
vector<int> a;
int n;
int number;
int b_find(int need_find) {
    int l = 0, r = n + 1;
    while(l + 1 < r) {
        int middle = (l + r) / 2;
        if(a[middle] <= need_find) {
            l = middle;
        }
        else {
            r = middle;
        }
    }
    return l;
}
void solve() {
    cin >> n >> number;
    a.resize(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cout << b_find(number) << endl;
}
int main() {
    solve();
    return 0;
}