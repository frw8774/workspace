#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int Q;
map<string, int> stu;
void solve() {
    cin >> Q;
    for(int i = 0; i < Q; i++) {
        int op;
        cin >> op;
        string name;
        int score;
        if(op == 1) {
            cin >> name >> score;
            auto it = stu.find(name);
            if(it != stu.end()) {
                it->second = score;
            }
            else {
                stu[name] = score;
            }
            cout << "OK" << endl;
        }
        else if(op == 2) {
            cin >> name;
            auto it = stu.find(name);
            if(it != stu.end()) {
                cout << stu.at(name) << endl;
            }
            else {
                cout << "Not found" << endl;
            }
        }
        else if(op == 3) {
            cin >> name;
            if(stu.erase(name) == 0) {
                cout << "Not found" << endl;
            }
            else {
                cout << "Deleted successfully" << endl;
            }
        }
        else if(op == 4) {
            cout << stu.size() << endl;
        }
    }
}
int main() {
    solve();
    return 0;
}