#include <bits/stdc++.h>
using namespace std;
int N, M;
vector<char> ans;
void result(int i, int j, char* x, char* y, int** len) {
    if(i == 0 || j == 0) {
        return;
    }
    if(x[i] == y[j]) {
        ans.push_back(x[i]);
        result(i - 1, j - 1, x, y, len);
    }
    else {
        if(len[i][j - 1] > len[i - 1][j]) {
            result(i, j - 1, x, y, len);
        }
        else {
            result(i - 1, j, x, y, len);
        }
    }
}
void dp(char *X, char *Y) {
    int** len = (int**)malloc(sizeof(int*) * (M + 1));
    for(int i = 0; i <= M; i++) {
        len[i] = (int*)malloc(sizeof(int) * N);
    }
    for(int i = 0; i <= M; i++) {
        len[i][0] = 0;
    }
    for(int i = 0; i <= N; i++) {
        len[0][i] = 0;
    }
    for(int i = 1; i <= M; i++) {
        for(int j = 1; j <= N; j++) {
            if(X[i] == Y[j]) {
                len[i][j] = len[i - 1][j - 1] + 1;
            }
            else {
                len[i][j] = max(len[i][j - 1], len[i - 1][j]);
            }
        }
    }
    cout << len[M][N] << endl;
    result(M, N, X, Y, len);
    reverse(ans.begin(), ans.end());
    for(char ch : ans) {
        cout << ch << " ";
    }
    cout << endl;
}
int main() {
    cin >> M >> N;
    char x[M + 1], y[N + 1];
    for(int i = 1; i <= M; i++) {
        cin >> x[i];
    }
    for(int i = 1; i <= N; i++) {
        cin >> y[i];
    }
    dp(x, y);
    return 0;
}