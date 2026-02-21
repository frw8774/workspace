#include <iostream>
#include <vector>
using namespace std;
#define N 10
int main() {
    // 1.初始化
    vector<int> a;                      //空的可变数组
    vector<int> a1(N);                   //10个元素，但未给每个元素赋值
    vector<int> a2(N, 2);               //10个元素，每个元素的值为2
    vector<int> a3 = {1, 2, 3, 4, 5};   //初始化列表

    // 2.添加与删除元素，时间复杂度为O(1)
    a.push_back(10);                    //尾部添加元素
    a.push_back(9);
    a.push_back(8);
    a.pop_back();                       //尾部删除元素

    // 3.遍历
    for(int i = 0;i < a3.size();i++) {
        cout << a3[i] << " ";
    }
    cout << endl;

    for(int i : a) {
        cout << i << " ";
    }
    cout << endl;

    for(vector<int>::iterator it = a3.begin();it != a3.end();it++) {
        cout << *it << " ";
    }
    cout << endl;

    // 4.插入元素（注意每次插入操作后迭代器会失效，需要重新赋值），时间复杂度为O(n)
    vector<int>::iterator it = a3.begin() + 2;
    a3.insert(it, 6);
    for(auto i : a3) {
        cout << i << " ";
    }
    cout << endl;

    it= a3.begin() + 2;
    a3.insert(it, 3, 7);
    for(auto i : a3) {
        cout << i << " ";
    }
    cout << endl;

    it = a3.begin() + 2;
    a3.insert(it, a.begin(), a.end());
    for(auto i : a3) {
        cout << i << " ";
    }
    cout << endl;

    // 5.删除元素，时间复杂度为O(n)
    a3.erase(a3.begin() + 2, a3.begin() + 4);
    for(auto i : a3) {
        cout << i << " ";
    }
    cout << endl;

    it = a3.begin() + 2;   
    a3.erase(it);
    for(auto i : a3) {
        cout << i << " ";
    }
    cout << endl;

    // 6.访问元素
    cout << a3[3] << endl;          //访问对应索引位置的元素（无越界检查）
    cout << a3.at(3) << endl;       //访问对应索引位置的元素（有越界检查）
    cout << a3.front() << endl;     //访问第一个元素
    cout << a3.back() << endl;      //访问最后一个元素
    
    // 7.其他方法
    cout << a3.size() << endl;      //数组大小
    cout << a3.empty() << endl;     //检查是否为空
}