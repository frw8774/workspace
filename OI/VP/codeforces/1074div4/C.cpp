#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
using namespace std;
typedef long long ll;
int t;
void solve() {
    int n;
    cin>>n;
    vector<ll> a(n);
    for(int i = 0;i < n;i++) {
        cin>>a[i];
    }
    set<ll> s(a.begin(), a.end());
    vector<ll> ua(s.begin(), s.end());
    ll max_mex = 0;
    for(ll num : s) {
        ll current = 0;
        while(s.count(num + current + 1)) {
            current++;
        }
        max_mex = max(max_mex, current + 1);
    }
    cout<<max_mex<<endl;
}
int main() {
    cin>>t;
    for(int i = 0;i < t;i++) {
        solve();
    }
    return 0;
}