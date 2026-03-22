#include <bits/stdc++.h>
using namespace std;
string a, b;
int arr_a[100000];
int arr_b[100000];
int res[100000];
int len_a, len_b, len;
string mul_plus(string a, string b) {
    string result;
    len_a = a.length();
    len_b = b.length();
    len = len_a + len_b;
    for(int i = 0; i < len_a; i++) {
        arr_a[i] = a[len_a - 1 - i] - '0';
    }
    for(int i = 0; i < len_b; i++) {
        arr_b[i] = b[len_b - 1 - i] - '0';
    }
    //模拟乘法
    for(int i = 0; i < len_a; i++) {
        for(int j = 0; j < len_b; j++) {
            res[i + j] += arr_a[i] * arr_b[j];
            res[i + j + 1] = res[i + j] / 10;
            res[i + j] = res[i + j] % 10;
        }
    }
    // 处理前导0
    while(len && res[len] == 0) {
        len--;
    }
    for(int i = len; i >= 0; i--) {
        result.append(to_string(res[i]));
    }
    return result;
}
void solve() {
    cin >> a >> b;
    memset(arr_a, 0, sizeof(arr_a));
    memset(arr_b, 0, sizeof(arr_b));
    memset(res, 0, sizeof(res));
    cout << mul_plus(a, b);
}
int main() {
    solve();
    return 0;
}