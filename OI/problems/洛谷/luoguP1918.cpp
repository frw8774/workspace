#include <bits/stdc++.h>
using namespace std;
int n, Q;
typedef struct {
    int num;
    int index;
} place;
bool compare(place a, place b) {
    return a.num < b.num;
}
place a[100005];
int b_search(int need_find) {
    int l = 1, r = n;
    while(l <= r) {
        int middle = l + (r - l) / 2;
        if(a[middle].num == need_find) {
            return a[middle].index;
        }
        if(a[middle].num > need_find) {
            r = middle - 1;
        }
        if(a[middle].num < need_find) {
            l = middle + 1;
        }
    }
    return 0;
}
void solve() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].num;
        a[i].index = i;
    }
    sort(a + 1, a + n + 1, compare);
    cin >> Q;
    int need[Q + 1];
    for(int i = 1; i <= Q; i++) {
        cin >> need[i];
    }
    for(int i = 1; i <= Q; i++) {
        cout << b_search(need[i]) << endl;
    }
}
int main() {
    solve();
    return 0;
}