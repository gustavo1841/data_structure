#include <iostream>

using namespace std;

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int val) : key(val), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    Node* root;

    // 获取节点高度
    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    // 计算平衡因子
    int getBalanceFactor(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // 更新高度
    void updateHeight(Node* node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    // 左旋
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    // 右旋
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    // 插入节点
    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        updateHeight(node);

        // 平衡因子
        int balance = getBalanceFactor(node);

        // LL型（右旋）
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // RR型（左旋）
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // LR型（左-右旋）
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL型（右-左旋）
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // 中序遍历
    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void display() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(25);
    tree.insert(5);
    tree.insert(15);

    tree.display();
    return 0;
}