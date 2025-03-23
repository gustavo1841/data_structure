#include <iostream>
using namespace std;

// B+树节点
class BPlusTreeNode {
public:
    int* keys;        // 存储关键字
    int t;            // 最小度
    BPlusTreeNode** C; // 子节点指针
    int n;            // 当前关键字个数
    bool leaf;        // 是否为叶子
    BPlusTreeNode* next; // 叶子节点的链表指针（支持范围查找）

    BPlusTreeNode(int _t, bool _leaf);
    void traverse();
    BPlusTreeNode* search(int k);
    void insertNonFull(int k);
    void splitChild(int i, BPlusTreeNode* y);
};

// B+树类
class BPlusTree {
public:
    BPlusTreeNode* root;
    int t;

    BPlusTree(int _t) { root = nullptr; t = _t; }
    void traverse() { if (root) root->traverse(); cout << endl; }
    BPlusTreeNode* search(int k) { return (root == nullptr) ? nullptr : root->search(k); }
    void insert(int k);
};

// 构造函数
BPlusTreeNode::BPlusTreeNode(int _t, bool _leaf) {
    t = _t;
    leaf = _leaf;
    keys = new int[2 * t - 1];
    C = new BPlusTreeNode * [2 * t];
    n = 0;
    next = nullptr;
}

// 遍历
void BPlusTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf) C[i]->traverse();
        cout << keys[i] << " ";
    }
    if (!leaf) C[i]->traverse();
}

// 查找
BPlusTreeNode* BPlusTreeNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i]) i++;
    if (leaf) return (keys[i] == k) ? this : nullptr;
    return C[i]->search(k);
}

// 插入
void BPlusTree::insert(int k) {
    if (!root) {
        root = new BPlusTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else {
        if (root->n == 2 * t - 1) {
            BPlusTreeNode* s = new BPlusTreeNode(t, false);
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
void BPlusTreeNode::insertNonFull(int k) {
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

// 分裂
void BPlusTreeNode::splitChild(int i, BPlusTreeNode* y) {
    BPlusTreeNode* z = new BPlusTreeNode(y->t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++) z->keys[j] = y->keys[j + t];
    if (!y->leaf) for (int j = 0; j < t; j++) z->C[j] = y->C[j + t];
    y->n = t - 1;
    for (int j = n; j >= i + 1; j--) C[j + 1] = C[j];
    C[i + 1] = z;
    keys[i] = y->keys[t - 1];
    n++;
    if (y->leaf) z->next = y->next, y->next = z; // 叶子节点链表
}

// **测试代码**
void testBPlusTree() {
    BPlusTree t(3);  // 3阶B+树
    int keys[] = { 10, 20, 5, 6, 12, 30, 7, 17 };
    cout << "插入关键字：" << endl;
    for (int k : keys) {
        cout << "插入 " << k << " 后的 B+ 树：";
        t.insert(k);
        t.traverse();
    }

    cout << "\n查找关键字：" << endl;
    int searchKeys[] = { 6, 15, 30 };
    for (int k : searchKeys) {
        cout << "查找 " << k << ": ";
        BPlusTreeNode* res = t.search(k);
        if (res) cout << "找到 " << k << "!" << endl;
        else cout << k << " 不存在" << endl;
    }
}

// 主函数
int main() {
    testBPlusTree();
    return 0;
}
