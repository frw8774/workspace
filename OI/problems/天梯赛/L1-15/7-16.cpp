#include <bits/stdc++.h>
using namespace std;
int N;
void solve() {
    cin >> N;
    for(int i = 0; i < N; i++) {
        string num;
        cin >> num;
        int sum1 = (num[0]) + (num[1]) + (num[2]);
        int sum2 = (num[3]) + (num[4]) + (num[5]);
        if(sum1 == sum2) {
            cout << "You are lucky!" << endl;
        }
        else {
            cout << "Wish you good luck." << endl;
        }
    }
}
int main() {
    solve();
    return 0;
}