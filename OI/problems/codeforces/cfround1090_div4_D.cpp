// #include <bits/stdc++.h>
// using namespace std;
// vector<int> arr;
// bool is_prime(int i) {
//     for(int j = 2; j * j <= i; j++) {
//         if(i % j == 0) {
//             return false;
//         }
//     }
//     return true;
// }
// void func() {
//     for(int i = 2; i < 1000000; i++) {
//         if(is_prime(i)) {
//             arr.push_back(i);
//         }
//     }
// }
// void solve() {
//     int n;
//     cin >> n;
//     for(int i = 1; i <= n; i++) {
//         cout << arr[i] * arr[i - 1] << " ";
//     }
//     cout << endl;
// }
// int main() {
//     int t;
//     cin >> t;
//     func();
//     for(int i = 0; i < t; i++) {
//         solve();
//     }
//     return 0;
// }
#include <bits/stdc++.h>
using namespace std;
const int MAX_PRIME = 2e6 + 10;
vector<long long> primes;  
bool is_prime[MAX_PRIME];
void init_primes() {
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i < MAX_PRIME; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
        for (int j = 0; j < primes.size() && i * primes[j] < MAX_PRIME; ++j) {
            is_prime[i * primes[j]] = false;
            if (i % primes[j] == 0) {
                break;
            }
        }
    }
}
void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        long long val = primes[i] * primes[i-1];
        cout << val << " ";
    }
    cout << endl;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init_primes();  
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}