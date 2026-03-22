#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
bool is_select[9] = {false};
vector<int> number; //存放临时数据
vector<vector<int>> ans; // 八位数全排列
void dfs(int index) {
    if(index > 8) {
        ans.push_back(number);
        return;
    }
    for(int i = 1; i <= 8; i++) {
        if(is_select[i]) {
            continue;
        }
        number.push_back(i);
        is_select[i] = true;
        dfs(index + 1);
        number.pop_back();
        is_select[i] = false;
    }
}
void func() {
    ll max_gcd = 0;
    ll prize = 1e18;
    for(vector<int> a : ans) {
        for(int pos = 0; pos <= 8; pos++) {
            for(int i = 1; i <= 8; i++) {
                ll _number = 0;
                ll x = 1;
                for(int j = 7; j >= pos; j--) {
                    _number += a[j] * x;
                    x *= 10;
                }
                _number += i * x;
                x *= 10;
                for(int j = pos - 1; j >= 0; j--) {
                    _number += a[j] * x;
                    x *= 10;
                }
                if(max_gcd < __gcd(_number, n)) {
                    max_gcd = __gcd(_number, n);
                    prize = _number;
                }
                else if(max_gcd == __gcd(_number, n)) {
                    if(_number < prize) {
                        prize = _number;
                    }
                }
            }
        }
    }
    cout << prize << endl;
}
void solve() {
    cin >> n;
    dfs(1);
    func();
}
int main() {
    solve();
    return 0;
}
