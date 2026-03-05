#include <bits/stdc++.h>
using namespace std;
string a, b;
int arr_a[100000];
int arr_b[100000];
int res[100000];
int len_a, len_b, len;
bool compare(int arr_a[], int arr_b[]) {
    if(len_a != len_b) {
        return len_a > len_b;
    }
    for(int i = len_a - 1; i >= 0; i--) {
        if(arr_a[i] != arr_b[i]) {
            return arr_a[i] > arr_b[i];
        }
    }
    return true;
}
string sub_plus(int arr_a[], int arr_b[]) {
    string result;
    for(int i = 0; i < len; i++) {
        if(arr_a[i] < arr_b[i]) {
            arr_a[i] += 10;
            arr_a[i + 1]--;
        }
        res[i] = arr_a[i] - arr_b[i];
    }
    while(len && res[len] == 0) {
        len--;
    }
    for(int i = len ; i >= 0; i--) {
        result.append(to_string(res[i]));
    }
    return result;
}
void solve() {
    memset(arr_a, 0, sizeof(arr_a));
    memset(arr_b, 0, sizeof(arr_b));
    memset(res, 0, sizeof(res));
    cin >> a >> b;
    len_a = a.length();
    len_b = b.length();
    len = max(len_a, len_b);
    for(int i = 0; i < len_a; i++) {
        arr_a[i] = a[len_a - 1 - i] - '0';
    }
    for(int i = 0; i < len_b; i++) {
        arr_b[i] = b[len_b - 1 - i] - '0';
    }    
    if(!compare(arr_a, arr_b)) {
        swap(arr_a, arr_b);
        cout << "-";
    }    
    cout << sub_plus(arr_a, arr_b) << endl; 
}
int main() {
    solve();
    return 0;
}