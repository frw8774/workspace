#include <bits/stdc++.h>
using namespace std;
int N;
map<int, string> p;
vector<int> num;
int avg = 0;
void solve() {
    cin >> N;
    for(int i = 0; i < N; i++) {
        int number;
        string name;
        cin >> name >> number;
        p[number] = name;
        num.push_back(number);
        avg += number;
    }
    avg = avg / N;
    avg /= 2;
    sort(num.begin(), num.end());
    auto pos = lower_bound(num.begin(), num.end(), avg);
    auto _pos = pos - 1;
    int n1 = *pos;
    int n2 = *_pos;
    int winner_n = abs(n1 - avg) > abs(n2 - avg) ? n2 : n1;
    cout << avg  << " " << p[winner_n];
}
int main() {
    solve();
    return 0;
}