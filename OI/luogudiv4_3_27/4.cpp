#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n;
    cin >> n;
    vector<set<int>> arr;
    int a[2 * n + 5];
    arr.resize(2 * n + 5);
    for(int i = 1; i <= 2 * n; i++) {
        int id;
        cin >> id;
        arr[id].insert(i);
        a[i] = id;
    }
    for(int i = 1; i <= 2 * n; i++) {
        int id = a[i];
        set<int> temp = arr[id];
        for(auto j = temp.begin(); j != temp.end(); j++) {
            if(*j != i) {
                cout << *j << " ";
            }
        }
    }
    cout << endl;
}
int main() {
    solve();
    return 0;
}