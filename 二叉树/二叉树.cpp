//

#include <iostream>
using namespace std;
typedef struct btnode {
    int data;
    struct btnode* lchild, * rchild;
}*BinTree;

//先序遍历
void preorder(BinTree bt) {
    if (bt != NULL) {
        cout << bt->data << endl;
        preorder(bt->lchild);
        preorder(bt->rchild);
    }
}
//中序遍历
void Inorder(BinTree bt) {
    if (bt!=NULL) {
        Inorder(bt->lchild);
        cout << bt->data << endl;
        Inorder(bt->rchild);
    }
}
//后续遍历
void Postorder(BinTree bt) {
    if (bt!=NULL) {
        Postorder(bt->lchild);
        Postorder(bt->rchild);
        cout<< bt->data << endl;
    }
}
int main()
{
    std::cout << "Hello World!\n";
}

