#include <bits/stdc++.h>
using namespace std;
set<int> arr;
void solve() {
    string N;
    cin >> N;
    for(int i = 0; i < N.size(); i++) {
        arr.insert(N[i] - '0');
    }
    int cnt[10] = {0};
    for(int i = 0; i < N.size(); i++) {
        cnt[N[i] - '0']++;
    }
    for(int num : arr) {
        cout << num << ":" << cnt[num] << endl;
    }
}
int main() {
    solve();
    return 0;
}