#include <bits/stdc++.h>
using namespace std;
string a;
int b;
int arr_a[100000];
int res[100000];
int len_a;
//高精度除低精度
string div_plus(string a, int b) {
    string result;
    len_a = a.length();
    int len = len_a;
    long long r = 0;
    for(int i = 0; i < len_a; i++) {
        arr_a[i] = a[len_a - 1 - i] - '0';
    }
    for(int i = len_a - 1; i >= 0; i--) {
        r = r * 10 + arr_a[i]; //被除数
        res[len_a - 1 - i] = r / b; //存商
        r = r % b; //求余
    }
    //先翻转再处理前导0
    reverse(res, res + len);
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
    memset(res, 0, sizeof(res));
    cout << div_plus(a, b) << endl;
}
int main() {
    solve();
    return 0;
}