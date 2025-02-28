#include <iostream>
using namespace std;

typedef struct LinkNode {
    int data;
    struct LinkNode *next;
}LinkNode;

typedef struct {
    LinkNode* front, * rear;
}LinkedQueue;

void init(LinkedQueue & Q) {
    Q.front = Q.rear = (LinkNode*)malloc(sizeof(LinkNode));//建立头结点
    Q.front->next = NULL;
}

bool isEmpty(LinkedQueue Q) {
    if (Q.front==Q.rear) {
        return true;
    }
    return false;
}

void EnQueue(LinkedQueue &Q,int data) {
    LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
    s->data = data;
    s->next = NULL;
    Q.rear->next = s;
    Q.rear = s;
   
}
bool DeQueue(LinkedQueue & Q) {
    if (Q.front==Q.rear) {
        return false;
    }
    LinkNode *p = Q.front->next;
    int x = p->data;
    cout << "出队：" <<x<< endl;
    if (Q.rear==p) {
        Q.rear = Q.front;
    }
    free(p);
    return true;
}

int main()
{
    LinkedQueue Q;
    init(Q);
    EnQueue(Q, 1);
    EnQueue(Q, 2);
    EnQueue(Q, 3);
    EnQueue(Q, 4);
    DeQueue(Q);
    DeQueue(Q);
    DeQueue(Q);
    DeQueue(Q);
}


