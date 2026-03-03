#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll mem[19];
ll func(int n) {
    ll ans = 0;
    if(n == 0) {
        return 1;
    }
    if(mem[n] != -1) {
        return mem[n];
    }
    for(int i = 1;i <= n;i++) {
        ans += func(i - 1) * func(n - i);
    }
    mem[n] = ans;
    return ans;
}
void solve() {
    cin >> n;
    memset(mem, -1, sizeof(mem));
    cout << func(n) << endl;
}
int main() {
    solve();
    return 0;
}