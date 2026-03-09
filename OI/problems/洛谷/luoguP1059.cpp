#include <bits/stdc++.h>
using namespace std;
set<int> s;
int N;
void solve() {
    cin >> N;
    for(int i = 0; i < N; i++) {
        int num;
        cin >> num;
        s.insert(num);
    }
    cout << s.size() << endl;
    for(auto it = s.begin(); it != s.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}
int main() {
    solve();
    return 0;
}