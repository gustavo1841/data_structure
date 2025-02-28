#include <iostream>
using namespace std;
typedef struct LinkNode {
    int data;
    struct LinkNode* next;
}*LiStatck;

bool initStatck(LiStatck &L) {
    L = (LiStatck)malloc(sizeof(LiStatck));
    L->next = NULL;
    return true;
}

bool isEmpty(LiStatck L) {
    if (L->next == NULL)
        return true;
    return false;
}
//先进后出
bool push(LiStatck&L,int data) {
    LinkNode *s = (LinkNode*)malloc(sizeof(LinkNode));
    //这样始终保持先加进去的节点永远在后面
    s->next = L->next;
    s->data = data;

    L->next = s;
    return true;
}

int pop(LiStatck& L) {
    LinkNode* p;
    if (isEmpty(L))
        return -1;
    p = L->next;
    int pop = p->data;
    //更新头指针0
    L->next = L->next->next;
    free(p);
    return pop;
}

int main()
{
    LiStatck L;
    initStatck(L);
    push(L, 1);
    push(L, 2);
    push(L, 3);
    push(L, 4);
    cout << pop(L) << endl;
    cout << pop(L) << endl;
    cout << pop(L) << endl;
    cout << pop(L) << endl;
}

