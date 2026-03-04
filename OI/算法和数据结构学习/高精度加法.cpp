#include <bits/stdc++.h>
using namespace std;
string a, b;
int arr_a[100000];
int arr_b[100000];
int res[100000];
string add_plus(string a, string b) {
    string result;
    int len_a = a.length();
    int len_b = b.length();
    int len = max(len_a, len_b);
    for(int i = 0; i < len_a; i++) {
        arr_a[i] = a[len_a - 1 - i] - '0';
    }
    for(int i = 0; i < len_b; i++) {
        arr_b[i] = b[len_b - 1 - i] - '0';
    }
    for(int i = 0; i < len; i++) {
        res[i] = arr_a[i] + arr_b[i];
        if(res[i] >= 10) {
            res[i] -= 10;
            res[i + 1]++;
        }
    }
    if(res[len]) {
        len++;
    }
    for(int i = len - 1; i >= 0; i--) {
        result.append(to_string(res[i]));
    }
    return result;
}
void solve() {
    memset(arr_a, 0, sizeof(arr_a));
    memset(arr_b, 0, sizeof(arr_b));
    memset(res, 0, sizeof(res));
    cin >> a >> b;
    cout << add_plus(a, b);
}
int main() {
    solve();
    return 0;
}