#include <iostream>

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int val) : data(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    // 左旋
    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left) y->left->parent = x;
        y->parent = x->parent;

        if (!x->parent)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    // 右旋
    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right) y->right->parent = x;
        y->parent = x->parent;

        if (!x->parent)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;

        y->right = x;
        x->parent = y;
    }

    // 插入修复
    void fixInsert(Node* z) {
        while (z->parent && z->parent->color == RED) {
            Node* grandparent = z->parent->parent;

            if (z->parent == grandparent->left) {
                Node* uncle = grandparent->right;
                if (uncle && uncle->color == RED) {
                    // 情况1：叔叔是红色，变色处理
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    z = grandparent; // 继续向上修复
                }
                else {
                    if (z == z->parent->right) {
                        // 情况2：叔叔是黑色，且z是右子节点，先左旋
                        z = z->parent;
                        leftRotate(z);
                    }
                    // 情况3：叔叔是黑色，且z是左子节点，右旋+变色
                    z->parent->color = BLACK;
                    grandparent->color = RED;
                    rightRotate(grandparent);
                }
            }
            else {
                Node* uncle = grandparent->left;
                if (uncle && uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    z = grandparent;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    grandparent->color = RED;
                    leftRotate(grandparent);
                }
            }
        }
        root->color = BLACK; // 确保根节点是黑色
    }

public:
    RedBlackTree() : root(nullptr) {}

    // 插入新节点
    void insert(int val) {
        Node* newNode = new Node(val);
        if (!root) {
            root = newNode;
            root->color = BLACK;
            return;
        }

        Node* parent = nullptr;
        Node* curr = root;

        while (curr) {
            parent = curr;
            if (val < curr->data)
                curr = curr->left;
            else
                curr = curr->right;
        }

        newNode->parent = parent;
        if (val < parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;

        fixInsert(newNode); // 调整红黑树
    }

    // 中序遍历
    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        std::cout << node->data << (node->color == RED ? " (R) " : " (B) ") << " ";
        inorder(node->right);
    }

    void display() {
        inorder(root);
        std::cout << std::endl;
    }
};

// 测试
int main() {
    RedBlackTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(5);
    tree.insert(1);
    tree.insert(12);

    tree.display();
    return 0;
}
