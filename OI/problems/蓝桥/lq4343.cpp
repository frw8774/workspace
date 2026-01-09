#include <iostream>
#include <vector>
using namespace std;
const int MOD = 1e9 + 7;
vector<long long> tree;
int n, q;
int leaf_start;
void input() {
    cin >> n >> q;
    leaf_start = 1LL << n;
    int tree_size = 2 * leaf_start;
    tree.resize(tree_size);
    for (int i = 1; i <= leaf_start; ++i) {
        cin >> tree[leaf_start + i - 1];
    }
    for (int i = leaf_start - 1; i >= 1; --i) {
        tree[i] = (tree[2 * i] * tree[2 * i + 1]) % MOD;
    }
    while (q--) {
        int x, v;
        cin >> x >> v;
        int pos = leaf_start + x - 1;
        tree[pos] = v % MOD;
        for (pos /= 2; pos >= 1; pos /= 2) {
            tree[pos] = (tree[2 * pos] * tree[2 * pos + 1]) % MOD;
        }
        cout << tree[1] << '\n';
    }
}
int main() {
    input();
    return 0;
}