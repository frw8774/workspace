#include <iostream>
using namespace std;
struct BTNode {
    string data;
    BTNode* lchild;
    BTNode* rchild;
};
BTNode* root;
void insertLeftChild(string data, BTNode* node) {}
void input() {
    string order;
    cin>>order;
    while(order != "exit") {
        if(order == "L") {
            string data;
            cin>>data;
            insertLeftChild(data, root);
        }
    }
}
int main() {
    return 0;
}