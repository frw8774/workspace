#include <bits/stdc++.h>
using namespace std;
int n;
int arr[10][10];
int is_valid() {
    for(int i = 1; i <= 9; i++) {
        int flag[10] = {0};
        for(int j = 1; j <= 9; j++) {
            if(arr[i][j] > 9 || arr[i][j] < 1) {
                return 0;
            }
            else {
                flag[arr[i][j]]++;
            }
        }
        for(int k = 1; k <= 9; k++) {
            if(flag[k] != 1) {
                return 0;
            }
        }
    }
    for(int i = 1; i <= 9; i++) {
        int flag[10] = {0};
        for(int j = 1; j <= 9; j++) {
            if(arr[j][i] > 9 || arr[j][i] < 1) {
                return 0;
            }
            else {
                flag[arr[j][i]]++;
            }
        }
        for(int k = 1; k <= 9; k++) {
            if(flag[k] != 1) {
                return 0;
            }
        }
    }
    for(int i = 1; i <= 7; i += 3) {
        for(int j = 1; j <= 7; j += 3) {
            int flag[10] = {0};
            for(int p = i; p <= i + 2; p++) {
                for(int q = j; q <= j + 2; q++) {
                    if(arr[p][q] > 9 || arr[p][q] < 1) {
                        return 0;
                    }
                    else {
                        flag[arr[p][q]]++;
                    }
                }
            }
            for(int k = 1; k <= 9; k++) {
                if(flag[k] != 1) {
                    return 0;
                }
            }
        }
    }
    return 1;
}
void solve() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        for(int p = 1; p <= 9; p++) {
            for(int q = 1; q <= 9; q++) {
                cin >> arr[p][q];
            }
        }
        cout << is_valid() << endl;
    }
}
int main() {
    solve();
    return 0;
}