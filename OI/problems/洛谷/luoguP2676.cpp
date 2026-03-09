#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N, B;
int cnt = 0;
void solve() {
    cin >> N >> B;
    ll a[N];
    for(int i = 0; i < N; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < N - 1; i++) {
        int max_index = i;
        for(int j = i + 1; j < N; j++) {
            if(a[max_index] < a[j]) {
                max_index = j;
            }
        }
        if(i != max_index) {
           swap(a[i], a[max_index]); 
        }
    }
    ll sum = 0;
    for(int i = 0; i < N; i++) {
        sum += a[i];
        if(sum > B) {
            cnt = i + 1;
            break;
        }
    }
    cout << cnt << endl;
}
int main() {
    solve();
    return 0;
}