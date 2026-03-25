#include <bits/stdc++.h>
using namespace std;
int a1, a2, n;
void solve() {
    cin >> a1 >> a2 >> n;
    vector<int> arr;
    arr.push_back(a1);
    arr.push_back(a2);
    int cnt = n - 2;
    for(int i = 2; i < n; i++) {
        int num = arr[i - 2] * arr[i - 1];
        if(num >= 10) {
            int n1 = num / 10;
            int n2 = num % 10;
            arr.push_back(n1);
            arr.push_back(n2);
        }
        else if(num < 10) {
            arr.push_back(num);
        }
    }
    for(int i = 0; i < n; i++) {
        if(i == n - 1) {
            cout << arr[i];
        }
        else {
            cout << arr[i] << " ";
        }
    }
}
int main() {
    solve();
    return 0;
}
