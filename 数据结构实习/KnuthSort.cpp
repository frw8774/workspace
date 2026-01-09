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
vector<int>a;

// 读取文件（文本模式，空格分隔）
void readFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "无法打开文件: " << filename << endl;
        return;
    }

    int num;
    while (inFile >> num) {
        a.push_back(num);
    }

    cout << "读取文件完成: " << filename << "，共 " << a.size() << " 个整数" << endl;
}

void KnuthSort() {
    int n = a.size();
    int gap = n / 2;
    while (gap >= 1) {
        for (int i = gap; i < n; ++i) {
            int temp = a[i];
            int j;
            for (j = i; j >= gap && a[j - gap] > temp; j -= gap) {
                a[j] = a[j - gap];
            }
            a[j] = temp;
        }
        gap = gap / 3 + 1;
        if (gap == 2) {
            gap = 1;
        } else if (gap == 1) {
            break;
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

    for (size_t i = 0; i < a.size(); ++i) {
        if (i > 0) outFile << " ";
        outFile << a[i];
    }

    cout << "排序结果已写入文本文件: " << filename << endl;
}

int main() {
    readFile("D:\\Test\\kspx\\data_10M.txt");
    auto start = chrono::high_resolution_clock::now();
    KnuthSort();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "排序耗时: " << duration.count() << " 毫秒" << endl;
    writeFile("C:\\Users\\Frw\\Desktop\\workspace\\10M_sorted.txt");    
    return 0;
}