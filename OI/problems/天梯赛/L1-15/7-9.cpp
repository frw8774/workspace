#include <bits/stdc++.h>
using namespace std;
vector<string> _name;
void solve() {
    string name;
    while(true) {
        cin >> name;
        if(name == ".") {
            break;
        }
        else {
            _name.push_back(name);
        }
    }
    int size = _name.size();
    if(size < 2) {
        cout << "Momo... No one is for you ...";
    }
    else if(size >= 2 && size < 14) {
        cout << _name[1] << " is the only one for you...";
    }
    else if(size >= 14) {
        cout << _name[1] << " and " << _name[13] << " are inviting you to dinner...";
    }
}
int main() {
    solve();
    return 0;
}