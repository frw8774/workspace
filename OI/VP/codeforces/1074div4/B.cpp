#include <iostream>
#include <vector>
using namespace std;
int t;
void solve() {
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i = 0;i < n;i++) {
        cin>>a[i];
    }
    int max_value = a[0];
    for(int i = 1;i < n;i++) {
        if(max_value < a[i]) {
            max_value = a[i];
        }
    }
    int ans = max_value * n;
    cout<<ans<<endl;
}
int main() {
    cin>>t;
    for(int i = 0;i < t;i++) {
        solve();
    }
    return 0;
}