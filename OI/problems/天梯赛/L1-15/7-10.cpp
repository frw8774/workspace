#include <bits/stdc++.h>
using namespace std;
int K;
vector<string> out;
map<string, string> m = {{"ChuiZi", "Bu"}, {"Bu", "JianDao"}, {"JianDao", "ChuiZi"}};
void solve() {
    cin >> K;
    string str;
    while(true) {
        cin >> str;
        if(str == "End") {
            break;
        }
        out.push_back(str);
    }
    int count = 0;
    for(string s : out) {
        if((count + 1) % (K + 1) == 0) {
            cout << s << endl;
        }
        else {
            cout << m[s] << endl;
        }
        count++;
    }
}
int main() {
    solve();
    return 0;
}