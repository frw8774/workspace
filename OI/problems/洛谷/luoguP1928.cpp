// #include <bits/stdc++.h>
// using namespace std;
// string msg;
// string func(string str) {
//     while(str.find('[') != string::npos && str.find(']') != string::npos) {
//         auto start = str.rfind('[');
//         auto end = str.find(']');
//         string _need = str.substr(start + 1, end - 1 - (start + 1) + 1);
//         string num;
//         string need_;
//         string s;
//         int n;
//         for(char ch : _need) {
//             if(ch >= '1' && ch <= '9') {
//                 num += ch;
//             }
//         }
//         if(num.size() == 2) {
//             n = (num[0] - '0') * 10 + num[1] - '0';
//             s = _need.substr(2);
//         }
//         else if(num.size() == 1) {
//             n = num[0] - '0';
//             s = _need.substr(1);
//         }
//         for(int i = 1; i <= n; i++) {
//             need_ += s;
//         }
//         str = str.substr(0, start) + need_ + str.substr(end + 1);  
//     }
//     return str;
// }
// void solve() {
//     getline(cin, msg);
//     cout << func(msg) << endl;
// }
// int main() {
//     solve();
//     return 0;
// } 
//上面这个是超内存过不了的
//下面这个是能过的
#include<bits/stdc++.h>
using namespace std;
string str;
string rep(string s)
{
    int t=0;
    for(int i=0;s[i];i++)
    {
        if(isdigit(s[i]))t=(t<<3)+(t<<1)+(s[i]^48);
        else break;
    }
    string x="",y="";
    for(int i=s.size()-1;i>=0;i--)
    {
        if(isalpha(s[i]))x+=s[i];
        else break;
    }
    reverse(x.begin(),x.end());
    while(t--)y+=x;
    return y;
}
int main()
{
    cin>>str;
    while(true)
    {
        int l=-1,r=-1;
        for(int i=str.size()-1;i>=0;i--)
        {
            if(str[i]=='[')
            {
                l=i;
                break;
            }
        }
        if(l==-1)break;
        for(int i=l;str[i];i++)
        {
            if(str[i]==']')
            {
                r=i;
                break;
            }
        }
        string ns="";
        for(int i=l+1;i<r;i++)ns+=str[i];
        str=str.replace(l,r-l+1,rep(ns));
    }
    cout<<str;
    return 0;
}
