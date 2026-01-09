#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<string>lines;
void input() {
    string line;
    while(getline(cin, line)) {
        size_t flag = line.find('E');
        if(flag != string::npos) {
            lines.push_back(line.substr(0, flag));
            break;
        }
        else {
            lines.push_back(line);
        }
    } 
}
void print11() {
    int w = 0, l = 0;
    for(string line : lines) {
        for(char ch : line) {
            if(ch == 'W') {
                w++;
            }
            else if(ch == 'L') {
                l++;
            }
            if((w >= 11 || l >= 11) && abs(w - l) >= 2) {
                cout<<w<<":"<<l<<endl;
                w = 0;
                l = 0;
            }
        }
    }
    cout<<w<<":"<<l<<endl;
}
void print21() {
    int w = 0, l = 0;
    for(string line : lines) {
        for(char ch : line) {
            if(ch == 'W') {
                w++;
            }
            if(ch == 'L') {
                l++;
            }
            if((w >= 21 || l >= 21) && abs(w - l) >= 2) {
                cout<<w<<":"<<l<<endl;
                w = 0;
                l = 0;
            }            
        }
    }
    cout<<w<<":"<<l<<endl;      
}
int main() {
    input();
    print11();
    cout<<endl;
    print21();
    return 0;
}