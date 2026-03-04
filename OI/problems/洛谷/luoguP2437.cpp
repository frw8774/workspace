#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int m, n;
string mem[1002];
string add_plus(string a, string b) {
    int arr_a[2000];
    int arr_b[2000];
    int res[2000];
    string add_res;
    memset(arr_a, 0, sizeof(arr_a));
    memset(arr_b, 0, sizeof(arr_b));
    memset(res, 0, sizeof(res));
    int len_a = a.length();
    int len_b = b.length();
    for(int i = 0;i < len_a;i++) {
        arr_a[len_a - 1 - i] = a[i] - '0';
    }
    for(int i = 0;i < len_b;i++) {
        arr_b[len_b - 1 - i] = b[i] - '0';
    }
    int len = max(len_a, len_b);
    for(int i = 0;i < len;i++) {
        res[i] += arr_a[i] + arr_b[i];
        if(res[i] >= 10) {
            res[i] -= 10;
            res[i + 1]++;
        }
    }
    int highest = len;
    while(res[highest] == 0 && highest > 0) {
        highest--;
    }
    for(int i = highest;i >= 0;i--) {
        add_res.append(to_string(res[i]));
    }
    return add_res;
}

string func(int k) {
    if(k == 0) {
        return "1";
    }
    if(k == 1) {
        return "1";
    }
    if(mem[k] != "-1") {
        return mem[k];
    }
    return mem[k] = add_plus(func(k - 1), func(k - 2));
}

void solve() {
    for(int i = 0;i < 1002;i++) {
        mem[i] = "-1";
    }
    cin >> m >> n;
    int dis = n - m;
    cout << func(dis) << endl;
}

int main() {
    solve();
    return 0;
}