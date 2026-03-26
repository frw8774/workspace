#include <bits/stdc++.h>
using namespace std;
string str;
void solve() {
    getline(cin, str);
    int cnt_g = 0, cnt_p = 0, cnt_l = 0, cnt_t = 0;
    for(int i = 0; i < str.size(); i++) {
        if(tolower(str[i]) == 'g') {
            cnt_g++;
        }
        else if(tolower(str[i]) == 'p') {
            cnt_p++;
        }
        else if(tolower(str[i]) == 'l') {
            cnt_l++;
        }
        else if(tolower(str[i]) == 't') {
            cnt_t++;
        }
    }
    int all = 4 * max(max(cnt_g, cnt_l), max(cnt_p, cnt_t)); 
    for(int i = 1; i <= all; i++) {
        if(i % 4 == 1) {
            if(cnt_g != 0) {
                cout << "G";
                cnt_g--;
            }
        }
        if(i % 4 == 2) {
            if(cnt_p != 0) {
                cout << "P";
                cnt_p--;
            }
        }
        if(i % 4 == 3) {
            if(cnt_l != 0) {
                cout << "L";
                cnt_l--;
            }
        }
        if(i % 4 == 0) {
            if(cnt_t != 0) {
                cout << "T";
                cnt_t--;
            }
        }
    }
}
int main() {
    solve();
    return 0;
}