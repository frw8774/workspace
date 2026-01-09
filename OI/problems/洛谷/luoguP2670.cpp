#include <iostream>
#include <vector>
#include <string>
using namespace std;
int n, m;
char ch[105][105];
void input() {
    cin>>n>>m;
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < m;j++) {
            cin>>ch[i][j];
        }
    }
}
int count(int i,int j) {
    int num = 0;
    if((i - 1) >= 0 && ch[i - 1][j] == '*') {
        num++;
    }
    if((i + 1) < n && ch[i + 1][j] == '*') {
        num++;
    }
    if((j - 1) >= 0 && ch[i][j - 1] == '*') {
        num++;
    }
    if((j + 1) < m && ch[i][j + 1] == '*') {
        num++;
    }
    if((i - 1) >= 0 && (j - 1) >= 0 && ch[i - 1][j - 1] == '*') {
        num++;
    }
    if((i - 1) >= 0 && (j + 1) < m && ch[i - 1][j + 1] == '*') {
        num++;
    }
    if((i + 1) < n && (j - 1) >= 0 && ch[i + 1][j - 1] == '*') {
        num++;
    }
    if((i + 1) < n && (j + 1) < m && ch[i + 1][j + 1] == '*') {
        num++;
    }
    return num;
}
void print() {
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < m;j++) {
            if(ch[i][j] == '*') {
                cout<<ch[i][j];
            }
            if(ch[i][j] == '?') {
                cout<<count(i, j);
            }
        }
        cout<<endl;
    }
}
int main() {
    input();
    print();
    return 0;
}