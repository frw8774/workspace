#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <fstream>
#include <random>
#include <chrono>
#include <string>
#include <sys/stat.h>
using namespace std;

vector<int> a;
vector<int> arr;
int maxDigit = 0;

// 读取文件（文本模式，空格分隔）
void readFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "无法打开文件: " << filename << endl;
        return;
    }

    int num;
    while (inFile >> num) { // 按空格读取 int
        a.push_back(num);
    }

    cout << "读取文件完成: " << filename << "，共 " << a.size() << " 个整数" << endl;
}

void getMaxDigit() {
    int maxValue = a[0];
    for(int i = 0;i < a.size();i++) {
        if(a[i] > maxValue) {
            maxValue = a[i];
        }
    }

    while(maxValue != 0){
        maxValue /= 10;
        maxDigit++;
    }
}

int getRadix(int x, int k, int maxDigit) {
    if(k < 1 || k > maxDigit) {
        return -1;
    }

    for(int i = 1;i <= maxDigit - k;i++) {
        x /= 10;
    }

    return x%10;
}

void MSD(int digit, vector<int>& nums) {
    if(digit > maxDigit) {
        return;
    }

    queue<int> q[10];
    for(int i = 0;i < nums.size();i++) {
        int x = getRadix(nums[i], digit, maxDigit);
        q[x].push(nums[i]);
    }

    nums.clear();
    for(int i = 0;i < 10;i++) {
        if(!q[i].empty()) {
            vector<int> temp;
            while(!q[i].empty()) {
                temp.push_back(q[i].front());
                q[i].pop();
            }
            MSD(digit + 1, temp);
            nums.insert(nums.end(), temp.begin(), temp.end());
        }
    }
}

// 写入文件（文本模式，空格分隔）
void writeFile(const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "无法创建文件: " << filename << endl;
        return;
    }

    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) outFile << " ";
        outFile << arr[i];
    }

    cout << "排序结果已写入文本文件: " << filename << endl;
}

int main() {
    readFile("D:\\Test\\kspx\\data_10M.txt");
    arr.resize(a.size());
    getMaxDigit();
    auto start = chrono::high_resolution_clock::now();
    MSD(1, a);
    arr = a;
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "排序耗时: " << duration.count() << " 毫秒" << endl;
    writeFile("C:\\Users\\Frw\\Desktop\\workspace\\10M_sorted.txt");    
    return 0;
}