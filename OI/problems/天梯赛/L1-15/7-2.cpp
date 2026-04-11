#include <bits/stdc++.h>
using namespace std;
int N;
int M;
map<int, pair<string, int>> msg;
void solve() {
    cin >> N;
    for(int i = 0; i < N; i++) {
        string id;
        int sj;
        int seat;
        cin >> id >> sj >> seat;
        msg[sj].first = id;
        msg[sj].second = seat;
    }
    cin >> M;
    for(int i = 0; i < M; i++) {
        int _sj;
        cin >> _sj;
        cout << msg[_sj].first << " " << msg[_sj].second << endl;
    }
}
int main() {
    solve();
    return 0;
}