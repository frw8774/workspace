#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
int t;
void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0;i < n;i++) {
        cin >> a[i];
    }
    for(int i = 0;i < a.size() - 1;i++) {
        for(int j = i + 1;j < a.size();j++) {
            if((a[j] % a[i]) % 2 == 0) {
                cout << a[i] << " " << a[j] << endl;
                return;
            }
        }
    }
    cout << -1 << endl;
}
int main() {
    cin >> t;
    for(int i = 0;i < t;i++) {
        solve();
    }
    return 0;
}