#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n, sum_a = 0, sum_b = 0;
    cin >> n;
    string ans = "";
    for(int i = 0; i < n; i++) {
        int num;
        cin >> num;
        if(i == 0 || sum_a == sum_b) {
            sum_a += num;
            ans += "A"; 
        }
        else if(sum_a > sum_b) {
            sum_b += num;
            ans += "B";
        }
        else if(sum_a < sum_b) {
            sum_a += num;
            ans += "A";
        }
    }
    cout << ans << endl;
}
int main() {
    solve();
    return 0;
}