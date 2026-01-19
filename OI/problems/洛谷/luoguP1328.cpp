#include <iostream>
using namespace std;
int N, NA, NB;
int compareTo(int a, int b) {
    if(a == 0) {
        if(b == 0) {
            return 0;
        }
        if(b == 2 || b == 3) {
            return 1;
        }        
        if(b == 1 || b == 4) {
            return -1;
        }
    }
    else if(a == 1) {
        if(b == 1) {
            return 0;
        }
        if(b == 0 || b == 3) {
            return 1;
        }
        if(b == 2 || b == 4) {
            return -1;
        }
    }
    else if(a == 2) {
        if(b == 2) {
            return 0;
        }
        if(b == 1 || b == 4) {
            return 1;
        }
        if(b == 0 || b == 3) {
            return -1;
        }
    }
    else if(a == 3) {
        if(b == 3) {
            return 0;
        }
        if(b == 2 || b == 4) {
            return 1;
        }
        if(b == 0 || b == 1) {
            return -1;
        }
    }
    else if(a == 4) {
        if(b == 4) {
            return 0;
        }
        if(b == 0 || b == 1) {
            return 1;
        }
        if(b == 2 || b == 3) {
            return -1;
        }
    }
}
void input() {
    int a_score = 0, b_score = 0;
    cin>>N>>NA>>NB;
    int a[NA], b[NB];
    for(int i = 0;i < NA;i++) {
        cin>>a[i];
    }
    for(int i = 0;i < NB;i++) {
        cin>>b[i];
    }
    for(int i = 0;i < N;i++) {
        if(compareTo(a[i % NA], b[i % NB]) == 1) {
            a_score++;
        }
        else if(compareTo(a[i % NA], b[i % NB]) == -1) {
            b_score++;
        }
    }
    cout<<a_score<<" "<<b_score<<endl;
}
int main() {
    input();
    return 0;
}