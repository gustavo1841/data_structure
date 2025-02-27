#include <iostream>
using namespace std;
//双向链表
typedef struct DNode{
    int data;
    struct DNode* prior,* next;
}DNode,DLinkList;

//初始化
DLinkList* init() {
    DLinkList*  L = (DLinkList*)malloc(sizeof(DLinkList));
    L->data = NULL;
    L->next = L;
    L->prior = L;
    return L;

}
//前插法
bool DLinkedListFrontInsert(DLinkList * p,int data) {
    DNode*s  = (DNode*)malloc(sizeof(DNode));
    s->data = data;
    s->next = p;
    s->prior = p->prior;

    p->prior->next = s;
    p->prior = s;
    return true;
}

//尾插法
bool DLinkedListBackInsert(DLinkList *p,int data) {
    DNode* s = (DNode*)malloc(sizeof(DNode));
    s->data = data;
    s->prior = p;
    s->next = p->next;

    p->next->prior = s;
    p->next = s;
    return true;
}
//链表节点删除
int DLDelete(DNode* p) {
    p->prior->next = p->next;
    p->next->prior = p->prior;
    int x = p->data;
    free(p);
    return x;
}

void PinrtLinkedList(DLinkList *p) {
    DNode* curr = p->next;
    while (curr!=p) {
        cout << "输出：" << curr->data << endl;
        curr = curr->next;
    }
}



int main()
{
    DLinkList* L = init();
    DLinkedListFrontInsert(L, 1);
    DLinkedListFrontInsert(L, 2);
    DLinkedListFrontInsert(L, 3);
    DLinkedListFrontInsert(L, 4);
    PinrtLinkedList(L);
    DLDelete(L->next->next->prior);
    cout<<"=========删除后========="<<endl;
    PinrtLinkedList(L);


}
