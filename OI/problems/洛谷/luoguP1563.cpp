#include <iostream>
#include <string>
#include <vector>
using namespace std;
int n,m;
struct people {
    int flag;
    string name;
};
vector<people>v;
int a[10000];
int s[10000];
void input() {
    cin>>n>>m;
    for(int i = 0;i < n;i++) {
        people p;
        cin>>p.flag>>p.name;
        v.push_back(p);
    }
    people p = v[0];
    int index = 0;
    for(int i = 0;i < m;i++) {
        int a, s;
        cin>>a>>s;
        if(p.flag == 0) {
            if(a == 0) {
                index = (n + index - s) % n;
                p = v[index];
            }
            else if(a == 1) {
                index = (index + s) % n;
                p = v[index];
            }
        }
        else if(p.flag == 1) {
            if(a == 0) {
                index = (index + s) % n;
                p = v[index];
            }
            else if(a == 1) {
                index = (n + index - s) % n;
                p = v[index];
            }
        }
    }
    cout<<p.name<<endl;
}
int main() {
    input();
    return 0;
}