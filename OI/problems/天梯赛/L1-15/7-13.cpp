#include <bits/stdc++.h>
using namespace std;
int L, N;
vector<int> arr;
void solve() {
    cin >> L >> N;
    N -= 1;
    while(N) {
        arr.push_back(N % 26);
        N /= 26;
    }
    if(arr.size() < L) {
        for(int i = arr.size(); i < L; i++) {
            arr.push_back(0);
        }
    }
    reverse(arr.begin(), arr.end());
    for(int i = 0; i < L; i++) {
        cout << (char)('z' - arr[i]);
    }
}
int main() {
    solve();
    return 0;
}