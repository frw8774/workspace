#include <bits/stdc++.h>
using namespace std;
int main() {
    string str, text, pattern;
    cin >> text >> pattern;
    str = pattern + "#" + text;
    vector<int> pi(str.size());
    for(int i = 1; i < str.size(); i++) {
        int j = pi[i - 1];
        while(j != 0 && str[j] != str[i]) {
            j = pi[j - 1];
        }
        if(str[i] == str[j]) {
            pi[i] = j + 1;
        }
    }
    for(int i = 0; i < pi.size(); i++) {
        if(pi[i] == pattern.size()) {
            cout << i - 2 * pi[i] << " ";
        }
    }
    cout << endl;
    return 0;
}