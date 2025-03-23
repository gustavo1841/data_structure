#include <iostream>

class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, int val) {
        if (!node) return new TreeNode(val);
        if (val < node->value) node->left = insert(node->left, val);
        else if (val > node->value) node->right = insert(node->right, val);
        return node;
    }

    bool search(TreeNode* node, int val) {
        if (!node) return false;
        if (val == node->value) return true;
        return val < node->value ? search(node->left, val) : search(node->right, val);
    }

    TreeNode* remove(TreeNode* node, int val) {
        if (!node) return nullptr;
        if (val < node->value) node->left = remove(node->left, val);
        else if (val > node->value) node->right = remove(node->right, val);
        else {
            if (!node->left) {
                TreeNode* rightChild = node->right;
                delete node;
                return rightChild;
            }
            else if (!node->right) {
                TreeNode* leftChild = node->left;
                delete node;
                return leftChild;
            }
            TreeNode* successor = node->right;
            while (successor->left) successor = successor->left;
            node->value = successor->value;
            node->right = remove(node->right, successor->value);
        }
        return node;
    }

    void inorder(TreeNode* node) {
        if (!node) return;
        inorder(node->left);
        std::cout << node->value << " ";
        inorder(node->right);
    }

public:
    BST() : root(nullptr) {}

    void insert(int val) { root = insert(root, val); }
    bool search(int val) { return search(root, val); }
    void remove(int val) { root = remove(root, val); }
    void inorder_traversal() { inorder(root); std::cout << std::endl; }
};

int main() {
    BST tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(4);
    tree.insert(6);

    tree.inorder_traversal(); // 3 4 5 6 7
    tree.remove(5);
    tree.inorder_traversal(); // 3 4 6 7

    return 0;
}