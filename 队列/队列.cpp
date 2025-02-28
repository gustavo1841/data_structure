

#include <iostream>
#define MaxSize 50
using namespace std;

typedef struct {
    int data[MaxSize];
    int front, rear;
}SqQueue;

void init(SqQueue& Q) {
    Q.rear = Q.front = 0;
}

bool isEmpty(SqQueue q) {
    if (q.front==q.rear) {
        return true;
    }
    return false;
}

bool EnQueue(SqQueue &Q,int data) {
    //队满
    if ((Q.rear+1)%MaxSize==Q.front) {
        return false;
    }
    Q.data[Q.rear] = data;
    //1%50 = 1、2%50=2、3%50=3....50%50=0，用这种方式就可以构造一个完整递进闭环
    Q.rear = (Q.rear + 1) %MaxSize;
    return true;
}

bool DeQueue(SqQueue &Q) {
    if (Q.rear==Q.front) {
        return false;
    }
    int x = Q.data[Q.front];
    cout << "出队：" << x << endl;
    //头指针后移
    Q.front = (Q.front + 1) % MaxSize;
    return true;

}


int main()
{
    SqQueue Q;
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
