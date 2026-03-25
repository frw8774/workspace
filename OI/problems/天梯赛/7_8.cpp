#include <bits/stdc++.h>
using namespace std;
int N;
vector<int> arr;
void solve() {
    cin >> N;
    int score;
    cin >> score;
    arr.push_back(score);
    int _max = score;
    int _min = score;
    int _maxcnt = 0;
    int _mincnt = 0;
    for(int i = 0; i < N - 1; i++) {
        int _score;
        cin >> _score;
        if(_max < _score) {
            _max = _score;
        }
        if(_min > _score) {
            _min = _score;
        }
        arr.push_back(_score);
    }
    for(int i = 0; i < N; i++) {
        if(arr[i] == _max) {
            _maxcnt++;
        }
        if(arr[i] == _min) {
            _mincnt++;
        }
    }
    cout << _min << " " << _mincnt << endl;
    cout << _max << " " << _maxcnt;
}
int main() {
    solve();
    return 0;
}