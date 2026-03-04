#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll mem[1002];
ll func(int n) {
    if(n == 1) {
        return 1;
    }
    if(mem[n] != -1) {
        return mem[n];
    }
    ll ans = 1;
    for(int i = 1;i <= n / 2;i++) {
        ans += func(i);
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