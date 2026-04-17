#include <bits/stdc++.h>
using namespace std;
int ra, ca, rb, cb;
void solve() {
    cin >> ra >> ca;
    int A[ra][ca];
    for(int i = 0; i < ra; i++) {
        for(int j = 0; j < ca; j++) {
            cin >> A[i][j];
        }
    }
    cin >> rb >> cb;
    int B[rb][cb];
    for(int i = 0; i < rb; i++) {
        for(int j = 0; j < cb; j++) {
            cin >> B[i][j];
        }
    }
    if(ca == rb) {
        int C[ra][cb];
        for(int i = 0; i < ra; i++) {
            for(int j = 0; j < cb; j++) {
                int sum = 0;
                for(int p = 0; p < ca; p++) {
                    sum += A[i][p] * B[p][j];
                }
                C[i][j] = sum;
            }
        }
        cout << ra  << " " << cb << endl;
        for(int i = 0; i < ra; i++) {
            for(int j = 0; j < cb; j++) {
                if(j == cb - 1 && i == ra - 1) {
                    cout << C[i][j];
                }
                else if(j == cb - 1 && i != ra - 1) {
                    cout << C[i][j] << endl;
                }
                else {
                    cout << C[i][j] << " ";
                }
            }
        }
    }
    else {
        cout << "Error: " << ca << " != " << rb;
    }
}
int main() {
    solve();
    return 0;
}