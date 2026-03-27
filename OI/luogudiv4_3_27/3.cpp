#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> arr;
    int _max = -1;
    int ans;
    bool flag = false;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if(i < k) {
            if(x > _max) {
                _max = x;
            }
        }
        if(i >= k) {
            if(x > _max) {
                if(flag == false) {
                    ans = x;
                    flag = true;
                }
            }
        }
        arr.push_back(x);
    }
    if(flag == false) {
        cout << arr[arr.size() - 1] << endl;
    }
    else if(flag == true) {
        cout << ans << endl;
    }
}
int main() {
    solve();
    return 0;
}