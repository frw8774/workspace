// #include <bits/stdc++.h>
// using namespace std;
// void solve() {
//     string str;
//     getline(cin, str);
//     stringstream ss(str);
//     vector<string> arr;
//     while(ss >> str) {
//         arr.push_back(str);
//     }
//     int x[2] = {0};
//     for(int i = 0; i < 2; i++) {
//         int cnt = 1;
//         for(int j = arr[i].size() - 1; j >= 0; j--) {
//             if(!isdigit(arr[i][j]) || arr[i][0] == '0') {
//                 x[i] = 0;
//                 break;
//             }
//             x[i] += (arr[i][j] - '0') * cnt;
//             cnt *= 10;
//         }
//     }
//     if(x[0] > 0 && x[0] <= 1000 && x[1] > 0 && x[1] <= 1000) {
//         cout << x[0] << " + " << x[1] << " = " << x[0] + x[1];
//     }
//     else if(x[0] > 0 && x[0] <= 1000 && x[1] == 0) {
//         cout << x[0] << " + ? = ?";
//     }
//     else if(x[1] > 0 && x[1] <= 1000 && x[0] == 0) {
//         cout << "? + " << x[1] << " = ?";
//     }
//     else if(x[0] == 0 && x[1] == 0) {
//         cout << "? + ? = ?";
//     }
// }
// int main() {
//     solve();
//     return 0;
// }
#include <bits/stdc++.h>
using namespace std;

// 封装判断函数：判断字符串是否是[1,1000]的正整数，返回对应数值（非法返回0）
int checkValid(string s) {
    // 1. 空字符串直接非法
    if (s.empty()) return 0;
    // 2. 检查是否全为数字
    for (char c : s) {
        if (!isdigit(c)) return 0;
    }
    // 3. 转整数（用字符串转整数，避免pow精度问题）
    long long num = 0; // 用long long防止超长数字溢出
    for (char c : s) {
        num = num * 10 + (c - '0');
        // 提前判断：超过1000直接返回0
        if (num > 1000) return 0;
    }
    // 4. 检查是否在[1,1000]范围
    if (num >= 1 && num <= 1000) {
        return (int)num;
    } else {
        return 0;
    }
}

void solve() {
    string str;
    getline(cin, str);
    // 分割第一个空格前的A和空格后的B（题目要求：第一个空格作为分隔）
    size_t firstSpace = str.find(' ');
    string A = str.substr(0, firstSpace);
    string B = str.substr(firstSpace + 1); // B非空（题目保证）
    
    int a = checkValid(A);
    int b = checkValid(B);
    
    // 按格式输出
    if (a != 0 && b != 0) {
        cout << a << " + " << b << " = " << a + b;
    } else if (a != 0 && b == 0) {
        cout << a << " + ? = ?";
    } else if (a == 0 && b != 0) {
        cout << "? + " << b << " = ?";
    } else {
        cout << "? + ? = ?";
    }
}

int main() {
    solve();
    return 0;
}