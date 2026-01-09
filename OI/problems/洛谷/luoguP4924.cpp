#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n, m;
void operation(int** a, int x, int y, int r, int z) {
    if(z == 0) {
        int arr[2 * r + 1][2 * r + 1];
        int p = 0, q = 0;
        for (int i = y - r; i <= y + r; i++) {
            for (int j = x + r; j >= x - r; j--) {
                arr[p][q] = a[j][i];
                q++;
                if (q >= 2 * r + 1) {
                    q = 0;
                }
            }
            p++;
        }
        int m = 0, n = 0;
        for (int i = x - r; i <= x + r; i++) {
            for (int j = y - r; j <= y + r; j++) {
                a[i][j] = arr[n][m];
                m++;
                if(m >= 2 * r + 1) {
                    m = 0;
                }
            }
            n++;
        }
    }
    else if(z == 1) {
        int arr[2 * r + 1][2 * r + 1];
        int p = 0, q = 0;
        for (int i = y + r; i >= y - r; i--) {
            for (int j = x - r; j <= x + r; j++) {
                arr[p][q] = a[j][i];
                q++;
                if (q >= 2 * r + 1) {
                    q = 0;
                }
            }
            p++;
        }
        int n = 0, m = 0;
        for (int i = x - r; i <= x + r; i++) {
            for (int j = y - r; j <= y + r; j++) {
                a[i][j] = arr[n][m];
                m++;
                if(m >= 2 * r + 1) {
                    m = 0;
                }                
            }
            n++; 
        }
    }
}
void input() {
    cin>>n>>m;
    int** a;
    a = (int **)malloc((n + 5) * sizeof(int *));
    for(int i = 0;i < n + 5;i++) {
        a[i] = (int *)malloc((n + 5) * sizeof(int));
    }
    for(int i = 1;i <= n;i++) {
        for(int j = 1;j <= n;j++) {
            a[i][j] = (i - 1) * n + j;
        }
    }
    for(int i = 0;i < m;i++) {
        int x, y, r, z;
        cin>>x>>y>>r>>z;
        operation(a, x, y, r, z);
    }
    for(int i = 1;i <= n;i++) {
        for(int j = 1;j <= n;j++) {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    for(int i = 0;i < n + 5;i++) {
        free(a[i]);
    }
    free(a);
}
int main() {
    input();
    return 0;
}