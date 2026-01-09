#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#define maxSize 100000
using namespace std;
long long value[maxSize];
int N;
int deep = 0;
void input() {
    cin>>N;
    int tree[N+5];
    for(int i = 1;i <= N;i++) {
        cin>>tree[i];
        if(pow(2, deep + 1) == i) {
            deep += 1;
        }
        if(pow(2, deep) <= i && pow(2, deep + 1) > i) {
            value[deep] += tree[i];
        }
    }    
}
int getMaxDeep() {
    int maxDeep = 0;
    long long maxSum = value[0];
    for(int i = 1;i <= deep;i++) {
        if(value[i] > maxSum) {
            maxDeep = i;
            maxSum = value[i];
        }
    }
    return maxDeep + 1;
}
int main() {
    input();
    cout<<getMaxDeep()<<endl;
    return 0;
}