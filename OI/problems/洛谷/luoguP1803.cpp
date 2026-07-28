#include <bits/stdc++.h>
using namespace std;
bool cmp(pair<int, int> p1, pair<int, int> p2) {
    return p1.second < p2.second;
}
int main() {
    int n;
    scanf("%d", &n);
    vector<pair<int, int>> v;
    for(int i = 0; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        pair<int, int> p;
        p.first = a;
        p.second = b;
        v.push_back(p);
    }
    sort(v.begin(), v.end(), cmp);
    int count = 1;
    int end = v[0].second;
    for(int i = 1; i < n; i++) {
        if(v[i].first >= end) {
            count++;
            end = v[i].second;
        }
    }
    printf("%d\n", count);
    return 0;
}