#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
bool cmp(pair<int, int> p1, pair<int, int> p2) {
    return p1.second < p2.second;
}
int main() {
    int n;
    scanf("%d", &n);
    vector<pair<int, int>> v;
    for(int i = 0; i < n; i++) {
        pair<int, int> p;
        p.first = i + 1;
        int t;
        scanf("%d", &t);
        p.second = t;
        v.push_back(p);
    }
    sort(v.begin(), v.end(), cmp);
    ll need_time[n];
    need_time[0] = 0;
    double sum = 0;
    for(int i = 0; i < v.size() - 1; i++) {
        need_time[i + 1] = v[i].second + need_time[i];
        sum += need_time[i + 1];
    }
    for(pair<int, int> p : v) {
        printf("%d ", p.first);
    }
    printf("\n");
    printf("%.2lf\n", sum / n);
    return 0;	
}
