#include <bits/stdc++.h>
using namespace std;
int a[10] = {1, 0, 2, 8, 7, 4, 5, 9, 3, 6};
int func(int p, int r) {
    int i = p, j = r + 1;
    int num = a[p];
    while(true) {
        while(a[++i] <= num && i <= r); //从左向右开始找大于基准的数
        while(a[--j] > num && j > p); //从右向左开始找小于基准的数
        if(i >= j) {
            break;
        }
        swap(a[i], a[j]);
    }
    swap(a[j], a[p]);
    return j;
}
void quicksort(int p, int r) {
    if(p < r) {
        int q = func(p, r);
        quicksort(p, q - 1);
        quicksort(q + 1, r);
    }
}
int main() {
    quicksort(0, 9);
    for(int i : a) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}