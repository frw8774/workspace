#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, k;
int cnt = 0;
vector<int>a;
vector<bool>is_prime_arr;
void func(ll num) {
    is_prime_arr.resize(num + 1, true);
    is_prime_arr[0] = false;
    is_prime_arr[1] = false;
    for(ll i = 2; i * i <= num; i++) {
        if(is_prime_arr[i]) {
            for(ll j = i * i; j <= num; j += i) {
                is_prime_arr[j] = false;
            }
        }
    }
}
void dfs(int start, ll sum, int step) {
    if(step == k) {
        if(is_prime_arr[sum] && sum <= is_prime_arr.size()) {
            cnt++;
        }
        return;
    }
    if(step + (n - start) < k) {
        return;
    }
    for(int i = start; i < n; i++) {
        ll new_sum = sum + a[i];
        if(new_sum > is_prime_arr.size() - 1) {
            continue;
        }
        dfs(i + 1, new_sum, step + 1);
    }
}
void solve() {
    cin >> n >> k;
    a.resize(n);
    ll max_num = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        max_num += a[i];
    }
    func(max_num);
    dfs(0, 0, 0);
    cout << cnt << endl;
}
int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    solve();
    return 0;
}