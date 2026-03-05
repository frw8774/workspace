#include <bits/stdc++.h>
using namespace std;
int p1, p2, p3;
string str;
string func(string str, int p1, int p2, int p3) {
    int pos = str.find("-", 0);
    if(pos == string::npos) {
        return str;
    }
    if(pos == 0 || pos == str.length() - 1) {
        return str.substr(0, pos + 1) + func(str.substr(pos + 1), p1, p2, p3);
    }
    string new_substr;
    char left = str[pos - 1];
    char right = str[pos + 1];
    bool is_valid = false;
    if (islower(left) && islower(right) && (left < right)) {
        is_valid = true;
        int count = right - left - 1;
        if (p1 == 1) {
            for (char ch = left + 1; ch < right; ch++) {
                new_substr.append(p2, ch);
            }
        }
        else if (p1 == 2) {
            for (char ch = left + 1; ch < right; ch++) {
                new_substr.append(p2, toupper(ch));
            }
        }
        else if (p1 == 3) {
            new_substr.append(count * p2, '*');
        }
    }
    if (isdigit(left) && isdigit(right) && (left < right)) {
        is_valid = true;
        int count = right - left - 1;
        if (p1 == 3) {
            new_substr.append(count * p2, '*');
        }
        else {
            for (char ch = left + 1; ch < right; ch++) {
                new_substr.append(p2, ch);
            }
        }    
    }
    if(p3 ==2) {
        reverse(new_substr.begin(), new_substr.end());
    }
    string new_str;
    if(is_valid) {
        new_str = str.substr(0, pos) + new_substr + func(str.substr(pos + 1), p1, p2, p3);
    }
    else {
        new_str = str.substr(0, pos + 1) + func(str.substr(pos + 1), p1, p2, p3);
    }
    return new_str;
}
void solve() {
    cin>>p1>>p2>>p3;
    cin>>str;
    str = func(str, p1, p2, p3);
    cout << str << endl;
}
int main() {
    solve();
    return 0;
}