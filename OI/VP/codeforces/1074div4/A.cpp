#include <iostream>
using namespace std;
int t;
void solve() {
    int n;
    cin>>n;
    for(int i = 1;i <= n;i++) {
        cout<<i<<" ";
    }
    cout<<endl;
}
int main() {
    cin>>t;
    for(int i = 0;i < t;i++) {
        solve();
    }
    return 0;
}