#include <bits/stdc++.h>
using namespace std;
int n;
typedef struct {
    int c;
    int m;
    int e;
    int all;
    int id;
} student;
void solve() {
    cin >> n;
    student stu[n + 1];
    for(int i = 1; i <= n; i++) {
        cin >> stu[i].c >> stu[i].m >> stu[i].e;
        stu[i].all = stu[i].c + stu[i].m + stu[i].e;
        stu[i].id = i;
    }
    for(int i = 1; i <= n - 1; i++) {
        int max_index = i;
        for(int j = i + 1; j <= n; j++) {
            if(stu[max_index].all < stu[j].all) {
                max_index = j;
            }
            else if(stu[max_index].all == stu[j].all) {
                if(stu[max_index].c < stu[j].c) {
                    max_index = j;
                }
                else if(stu[max_index].c == stu[j].c) {
                    if(stu[max_index].id > stu[j].id) {
                        max_index = j;
                    }
                }
            }
        }
        if(max_index != i) {
           swap(stu[i], stu[max_index]); 
        }
    }
    for(int i = 1; i <= 5; i++) {
        cout << stu[i].id << " " << stu[i].all << endl;
    }
}
int main() {
    solve();
    return 0;
}