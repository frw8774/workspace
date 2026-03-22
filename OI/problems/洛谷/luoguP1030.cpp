#include <bits/stdc++.h>
using namespace std;
string mid, after, before;
void func(string mid, string after) {
    if(mid.empty() || after.empty()) {
        return;
    }
    int pos = mid.find(after[after.size() - 1]);
    before += mid[pos];
    func(mid.substr(0, pos), after.substr(0, pos));
    func(mid.substr(pos + 1), after.substr(pos, after.length() - pos - 1));
}
void solve() {
    cin >> mid >> after;
    func(mid, after);
    cout << before << endl;
}
int main() {
    solve();
    return 0;
}