#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
int t;

bool check(ll a, ll b) {
    if(a % b == 0) {
        return false;
    }
    return true;
}

void solve() {
    int n;
    cin>>n;
    vector<ll> a(n);
    for(int i = 0;i < n;i++) {
        cin>>a[i];
    }
    vector<ll> ans_array = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
    for(ll i : ans_array) {
        bool flag = false;
        for(ll j : a) {
            if(check(j, i)) {
                flag = true;
                break;
            }
        }
        if(flag) {
            cout<<i<<endl;
            break;
        }
    }
}

int main() {
    cin>>t;
    for(int i = 0;i < t;i++) {
        solve();
    }
    return 0;
}
