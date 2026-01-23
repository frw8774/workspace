#include <iostream>
using namespace std;
int N;
int flag;
void input() {
    cin>>N;
    int a[N + 1];
    for (size_t i = 0; i < N + 1; i++) {
        cin>>a[i];
    }
    if(N == 0) {
        cout<<a[0];
        return;
    }
    else if(N == 1) {
        for(size_t i = 0; i < N + 1; i++) {
            if(i == 0) {
                if(a[i] == 1) {
                    cout<<"x";
                }
                else if(a[i] == -1) {
                    cout<<"-x";
                }
                else {
                    string str = to_string(a[i]) + "x";
                    cout<<str;
                }
            }
            else {
                if(a[i] > 0) {
                    cout<<"+"<<a[i];
                }
                else if(a[i] < 0) {
                    cout<<a[i];
                }
                else {
                    continue;
                }
            }
        }
    }
    else {
    for (size_t i = 0; i < N + 1; i++) {
        /* code */
        if(i == 0) {
            if(a[i] == 1) {
                string str = "x^" + to_string(N - i);
                cout<<str;
            }
            else if(a[i] == -1) {
                string str = "-x^" + to_string(N - i);
                cout<<str;
            }
            else {
                string str = to_string(a[i]) + "x^" + to_string(N - i);
                cout<<str;
            }
        }
        else if(i != 0 && i != N && i != N - 1) {
            if(a[i] != 0) {
                if(a[i] == 1) {
                    string str = "+x^" + to_string(N - i);
                    cout<<str;                    
                }
                else if(a[i] == -1) {
                    string str = "-x^" + to_string(N - i);
                    cout<<str;
                }
                else {
                    if(a[i] > 0) {
                        string str = "+" + to_string(a[i]) + "x^" + to_string(N - i);
                        cout<<str;
                    }
                    else if(a[i] < 0) {
                        string str = to_string(a[i]) + "x^" + to_string(N - i);
                        cout<<str;
                    }                    
                }
            }
            if(a[i] == 0) {
                continue;
            }
        }
        else if(i == N - 1) {
            if(a[i] != 0) {
                if(a[i] == 1) {
                    string str = "+x";
                    cout<<str;                    
                }
                else if(a[i] == -1) {
                    string str = "-x";
                    cout<<str;
                }
                else {
                    if(a[i] > 0) {
                        string str = "+" + to_string(a[i]) + "x";
                        cout<<str;
                    }
                    else if(a[i] < 0) {
                        string str = to_string(a[i]) + "x";
                        cout<<str;
                    }                    
                }
            }
            if(a[i] == 0) {
                continue;
            }            
        }
        else if(i == N) {           
            if(a[i] != 0) {
                if(a[i] > 0) {
                    cout<<"+"<<a[i];
                }
                if(a[i] < 0) {
                    cout<<a[i];
                }
            }
            if(a[i] == 0) {
                continue;
            }
        }
    }          
    }
}
int main() {
    input();
    return 0;
}