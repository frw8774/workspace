#include <bits/stdc++.h>
using namespace std;
int N;
vector<int> v;
int cnt = 0;
int b_Sort() {
    for(int i = 0; i < N - 1; i++) {
        for(int j = 0; j < N - 1 - i; j++) {
            if(v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
                cnt++;
            }
        }
    }
    return cnt;
}
void solve() {
    cin >> N;
    v.resize(N);
    for(int i = 0; i < N; i++) {
        cin >> v[i];
    }
    cout << b_Sort() << endl;
}
int main() {
    solve();
    return 0;
}