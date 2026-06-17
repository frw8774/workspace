#include <bits/stdc++.h>
using namespace std;
int num = 1;
int chess[8][8];
void chessBoard(int tr, int tc, int dr, int dc, int size) {
    if(size == 1) {
        return;
    }

    int t = num++;
    int s = size / 2;

    //填充左上角棋盘
    if(dr < tr + s && dc < tc + s) {
        chessBoard(tr, tc, dr, dc, s);
    }
    else {
        chess[tr + s - 1][tc + s - 1] = t;
        chessBoard(tr, tc, tr + s - 1, tc + s - 1, s);
    }
    
    //填充右上角棋盘
    if(dr < tr + s && dc >= tc + s) {
        chessBoard(tr, tc + s, dr, dc, s);
    }
    else {
        chess[tr + s - 1][tc + s] = t;
        chessBoard(tr, tc + s, tr + s - 1, tc + s, s);
    }

    //填充左下角棋盘
    if(dr >= tr + s && dc < tc + s) {
        chessBoard(tr + s, tc, dr, dc, s);
    }
    else {
        chess[tr + s][tc + s - 1] = t;
        chessBoard(tr + s, tc, tr + s, tc + s - 1, s);
    }
    
    //填充右下角棋盘
    if(dr >= tr + s && dc >= tc + s) {
        chessBoard(tr + s, tc + s, dr, dc, s);
    }
    else {
        chess[tr + s][tc + s] = t;
        chessBoard(tr + s, tc + s, tr + s, tc + s, s);
    }
}
int main() {
    chessBoard(0, 0, 7, 7, 8);
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            cout << chess[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}