#include <bits/stdc++.h>
using namespace std;
int n0, n1, n;
vector<int> _n0, _n1;
vector<pair<int, int>> ans; 
void solve() {
    cin >> n0 >> n1 >> n;
    for(int i = 2; i <= n0; i++) {
        if(n0 % i == 0) {
            _n0.push_back(i);
        }
    }
    for(int i = 2; i <= n1; i++) {
        if(n1 % i == 0) {
            _n1.push_back(i);
        }
    }
    for(int a : _n0) {
        for(int b : _n1) {
            if((n0 / a) + (n1 / b) == n) {
                pair<int, int> temp;
                temp.first = a;
                temp.second = b;
                ans.push_back(temp);
            }
        }
    }
    if(ans.size() == 0) {
        cout << "No Solution" << endl;
        return;
    }
    int answer = 100000;
    pair<int, int> res;
    for(pair<int, int> p : ans) {
        if(abs(p.first - p.second) < answer) {
            answer = abs(p.first - p.second);
            res = p;
        }
    }
    cout << n0 / (res.first) << " " << n1 / (res.second) << endl;
}
int main() {
    solve();
    return 0;
}