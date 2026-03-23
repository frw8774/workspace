#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a, b;
vector<ll> ans;
int get_len(ll num) {
    int cnt = 0;
    while(num >= 10) {
        ll temp = 1;
        while(num) {
            temp = temp * (num % 10);
            num /= 10;
        }
        num = temp;
        cnt++;
    }
    return cnt;
}
void solve() {
    cin >> a >> b;
    int max_len = 0;
    for(ll i = a; i <= b; i++) {
        if(get_len(i) > max_len) {
            max_len = get_len(i);
            ans.clear();
            ans.push_back(i);
        }
        else if(get_len(i) == max_len) {
            ans.push_back(i);
        }
    }
    cout << max_len << endl;
    if(ans.size() > 1) {
        for(int i = 0; i < ans.size() - 1; i++) {
            cout << ans[i] << " ";
        }
        cout << ans[ans.size() - 1];
    }
    else if(ans.size() == 1) {
        cout << ans[0];
    }
}
int main() {
    solve();
    return 0;
}