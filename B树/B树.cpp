#include <iostream>
using namespace std;

// B 树节点类
class BTreeNode {
public:
    int* keys;      // 存储关键字
    int t;          // 最小度
    BTreeNode** C;  // 子节点数组
    int n;          // 当前关键字个数
    bool leaf;      // 是否为叶子节点

    BTreeNode(int _t, bool _leaf); // 构造函数
    void traverse();  // 遍历
    BTreeNode* search(int k); // 查找
    void insertNonFull(int k); // 插入
    void splitChild(int i, BTreeNode* y); // 分裂子节点
};

// B 树类
class BTree {
public:
    BTreeNode* root;
    int t; // 最小度

    BTree(int _t) { root = nullptr; t = _t; }
    void traverse() { if (root) root->traverse(); cout << endl; }
    BTreeNode* search(int k) { return (root == nullptr) ? nullptr : root->search(k); }
    void insert(int k);
};

// 构造函数
BTreeNode::BTreeNode(int _t, bool _leaf) {
    t = _t;
    leaf = _leaf;
    keys = new int[2 * t - 1];  // 最多存储 2t-1 个关键字
    C = new BTreeNode * [2 * t]; // 最多 2t 个子节点
    n = 0;
}

// 遍历节点
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf) C[i]->traverse();
        cout << keys[i] << " ";
    }
    if (!leaf) C[i]->traverse();
}

// 查找关键字
BTreeNode* BTreeNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i]) i++;
    if (keys[i] == k) return this;
    if (leaf) return nullptr;
    return C[i]->search(k);
}

// 插入关键字（主入口）
void BTree::insert(int k) {
    if (!root) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else {
        if (root->n == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            int i = (s->keys[0] < k) ? 1 : 0;
            s->C[i]->insertNonFull(k);
            root = s;
        }
        else {
            root->insertNonFull(k);
        }
    }
}

// 插入到非满节点
void BTreeNode::insertNonFull(int k) {
    int i = n - 1;
    if (leaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n++;
    }
    else {
        while (i >= 0 && keys[i] > k) i--;
        if (C[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, C[i + 1]);
            if (keys[i + 1] < k) i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

// 分裂子节点
void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++) z->keys[j] = y->keys[j + t];
    if (!y->leaf) for (int j = 0; j < t; j++) z->C[j] = y->C[j + t];
    y->n = t - 1;
    for (int j = n; j >= i + 1; j--) C[j + 1] = C[j];
    C[i + 1] = z;
    for (int j = n - 1; j >= i; j--) keys[j + 1] = keys[j];
    keys[i] = y->keys[t - 1];
    n++;
}

// **调试代码**
void testBTree() {
    BTree t(3);  // 3 阶 B 树

    int keys[] = { 10, 20, 5, 6, 12, 30, 7, 17 };
    cout << "插入关键字：" << endl;
    for (int k : keys) {
        cout << "插入 " << k << " 后的 B 树：";
        t.insert(k);
        t.traverse();
    }

    cout << "\n查找关键字：" << endl;
    int searchKeys[] = { 6, 15, 30 };
    for (int k : searchKeys) {
        cout << "查找 " << k << ": ";
        BTreeNode* res = t.search(k);
        if (res) cout << "找到 " << k << "!" << endl;
        else cout << k << " 不存在" << endl;
    }
}

// 主函数
int main() {
    testBTree();
    return 0;
}