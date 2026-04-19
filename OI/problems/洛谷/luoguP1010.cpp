#include <bits/stdc++.h>
using namespace std;
int n;
void func(int num) {
    if(num == 0) {
        cout << "0";
        return;
    }
    else if(num == 1) {
        cout << "2";
        return;
    }
    vector<int> arr;
    for (int i = 0; num > 0; i++) {
        if (num % 2 == 1) {
            arr.push_back(i);
        }
        num /= 2;
    }
    reverse(arr.begin(), arr.end());
    for (int i = 0; i < arr.size(); i++) {
        if (i > 0) {
            cout << "+";
        }
        if(arr[i] == 1) {
            cout << "2";
        }
        else {
            cout << "2(";
            func(arr[i]);
            cout << ")";
        }
    }
}
void solve() {
    cin >> n;
    func(n);
}
int main() {
    solve();
    return 0;
}