#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <fstream>
#include <random>
#include <chrono>
#include <string>
#include <sys/stat.h>
using namespace std;
vector<int>a;
vector<int>arr;

void input() {
    int x;
    while((cin>>x) && (x!=-1)) {
        a.push_back(x);
    }
}

void insertSort() {
    arr.push_back(a[0]);
    for(int i = 1;i < a.size();i++) {
        int index = arr.size();
        for(int j = 0;j < arr.size();j++) {
            if(a[i] < arr[j]) {
                index = j;
                break;
            }
        }
        arr.insert(arr.begin() + index, a[i]);
    }
    for(int i = 0;i < arr.size();i++) {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}
int main() {
    input();
    insertSort();
    return 0;
}