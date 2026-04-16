#include <bits/stdc++.h>
using namespace std;
int N;
string id;
vector<string> arr;
int p[17] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
map<int, int> zm = {{0, 1}, {1, 0}, {2, 24}, {3, 9}, {4, 8}, {5, 7}, {6, 6}, {7, 5}, {8, 4}, {9, 3}, {10, 2}};
void solve() {
    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> id;
        arr.push_back(id);
    }
    bool allvalid = true;
    for(string s : arr) {
        bool isvalid = true;
        int sum = 0;
        for(int i = 0; i < 17; i++) {
            if(!isdigit(s[i])) {
                isvalid = false;
                allvalid = false;
                break;
            }
            sum += (s[i] - '0') * p[i];
        }
        sum %= 11;
        if(s[17] == 'X') {
            if(zm[sum] != 24) {
                isvalid = false;
                allvalid = false;
            }
        }
        if(s[17] != 'X') {
            if(zm[sum] != s[17] - '0') {
                isvalid = false;
                allvalid = false;
            }
        }
        if(!isvalid) {
            cout << s << endl;
        }
    }
    if(allvalid) {
        cout << "All passed";
    }
}
int main() {
    solve();
    return 0;
}