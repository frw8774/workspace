#include <iostream>
using namespace std;
typedef long long ll;
ll a, n;
void input() {
    cin>>a>>n;
}
ll quickpow(ll a, ll n) {
    int res = 1;
    while(n) {
        if(n & 1) {
            res *= a;
        }
        a *= a;
        n /= 2;
    }
    return res;
}
int main() {
    input();
    cout<<quickpow(a, n)<<endl;
}

// 快速幂本质是对指数进行二进制分解，让指数和1进行按位与操作，如果结果为一，就让res乘上a，res一开始为1，a一开始为底数的值，之后每循环一次就平方一下
// 每次循环还需要将指数右移1位，等价于将指数除2
// 关于位运算符，见位运算.md这个文件
