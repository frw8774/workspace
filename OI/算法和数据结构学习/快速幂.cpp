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
