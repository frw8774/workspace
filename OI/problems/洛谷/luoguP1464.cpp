#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mem[21][21][21];
ll func(ll a, ll b, ll c) {
    if(a <= 0 || b <= 0 || c <= 0) {
        return 1ll;
    }
    else if(a > 20 || b > 20 || c > 20) {
        return func(20, 20, 20);
    }
    else if(mem[a][b][c] != -1) {
        return mem[a][b][c];
    }
    else if(a < b && b < c) {
        return mem[a][b][c] = func(a, b, c - 1) + func(a, b - 1, c - 1) - func(a, b - 1, c);
    }
    return mem[a][b][c] = func(a - 1, b, c) + func(a - 1, b - 1, c) + func(a - 1, b, c - 1) - func(a - 1, b - 1, c - 1);
}
int main() {
    ll a, b, c;
    memset(mem, -1, sizeof(mem));
    while(true) {
        cin >> a >> b >> c;
        if(a == -1 && b == -1 && c == -1) {
            break;
        }
        printf("w(%lld, %lld, %lld) = %lld\n", a, b, c, func(a, b, c));
    }
    return 0;
}
//记忆化递归存储数据的时机是在某个子问题的结果被完整计算出来后才存入数组
//一般流程是首先确认递归的边界条件，之后再检查数组中是否有当前问题的结果，有则直接返回，没有就进行递归计算
//之后计算子问题，当某个子问题的最终结果计算完后，将之存入数组并返回结果