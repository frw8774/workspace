#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N, C;
void solve() {
    cin >> N >> C;
    ll a[N];
    for(int i = 0; i < N; i++) {
        cin >> a[i];
    }
    sort(a, a + N);
    ll ans = 0, l = 0, r = 0;
    for(int i = 0; i < N; i++) {
        while(a[l] - a[i] < C && l < N) {
            l++;
        }
        while(a[r] - a[i] <= C && r < N) {
            r++;
        }
        ans += r - l;
    }
    cout << ans;
}
int main() {
    solve();
    return 0;
}