#include <bits/stdc++.h>
using namespace std;
bool cmp(pair<int, int> p1, pair<int, int> p2) {
    double v1 = (double)p1.second / p1.first;
    double v2 = (double)p2.second / p2.first;
    return v1 > v2;
}
int main() {
    int n, t;
    scanf("%d %d", &n, &t);
    vector<pair<int, int>> v;
    for(int i = 0; i < n; i++) {
        pair<int, int> p;
        int M, V;
        scanf("%d %d", &M, &V);
        p.first = M;
        p.second = V;
        v.push_back(p);
    }
    sort(v.begin(), v.end(), cmp);
    double value = 0;
    for(pair<int, int> p : v) {
        if(t > 0) {  
            if(t > p.first) {
                t -= p.first;
                value += p.second;
            }
            else if(t <= p.first) {
                value = value + ((double)t / p.first) * p.second;
                t = 0;
            }
        }
    }
    printf("%.2lf\n", value);
    return 0;
}