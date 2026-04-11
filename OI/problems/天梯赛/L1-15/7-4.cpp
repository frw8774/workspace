#include <bits/stdc++.h>
using namespace std;
int A_d, B_d, N;
void solve() {
    cin >> A_d >> B_d;
    cin >> N;
    int A_drink = 0, B_drink = 0;
    for(int i = 0; i < N; i++) {
        int A_shout, A_, B_shout, B_;
        cin >> A_shout >> A_ >> B_shout >> B_;
        int sum = A_shout + B_shout;
        if(A_ == sum && B_ != sum) {
            A_drink++;
        }
        if(B_ == sum && A_ != sum) {
            B_drink++;
        }
        if(A_drink > A_d) {
            cout << "A" << endl;
            cout << B_drink << endl;
            break;
        }
        if(B_drink > B_d) {
            cout << "B" << endl;
            cout << A_drink << endl;
            break;
        }
    }
}
int main() {
    solve();
    return 0;
}