#include <bits/stdc++.h>
using namespace std;
void solve() {
    int a, b, m, c, d, k;
    int cnt = 0;
    cin >> a >> b >> m >> c >> d >> k;
    int min = b, hour = a, _hour = a;
    bool flag = false;
    if(c <= a && d <= b) {
        c = 24 + c;
    }
    while(cnt < m / k) {
        _hour += (min + k) / 60;
        hour = (hour + (min + k) / 60) % 24;
        min = (min + k) % 60;
        cnt ++;
        if((_hour > c || (_hour == c && min > d)) && flag == false) {
            if(hour == 0) {
                hour = 23;
            } 
            else {
                hour -= 1;
            }
            flag = true;
        }
        cout << hour << " " << min << endl;
    }
}
int main() {
    solve();
    return 0;
}