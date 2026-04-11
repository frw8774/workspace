#include <bits/stdc++.h>
using namespace std;
string num;
void solve() {
    cin >> num;
    int cnt_2 = 0;
    int size = 0;
    for(int i = 0; i < num.size(); i++) {
        if(num[i] - '2' == 0) {
            cnt_2++;
        }
        if(isdigit(num[i])) {
            size++;
        }
    }
    double degree;
    degree = (double)cnt_2 / size;
    if(num[0] == '-') {
        degree *= 1.5;
    }
    if(num[num.size() - 1] == '0' || num[num.size() - 1] == '2' || num[num.size() - 1] == '4' || num[num.size() - 1] == '6' || num[num.size() - 1] == '8') {
        degree *= 2;
    }
    degree *= 100;
    printf("%.2f\%\n", degree);
}
int main() {
    solve();
    return 0;
}