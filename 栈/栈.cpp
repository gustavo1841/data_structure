
#include <iostream>
using namespace std;

#define MaxSize 50
typedef struct {
    int data[MaxSize];
    int top;
}SqStack;

//顺序栈
void InitStack(SqStack &S) {
    S.top = -1;//初始化栈顶指针
}
//判空
bool StatckEmpty(SqStack S) {
    if (S.top == -1)
        return true;
    else
        return false;
}
//进栈
bool push(SqStack& S, int data) {
    if (S.top == MaxSize - 1)
        return false;
    cout << "指针：" << S.top << endl;
    S.data[++S.top] = data;
    cout << "压栈成功：" << S.top << endl;
    return true;
}
//出栈
bool pop(SqStack &S,int &x) {
    if (S.top == -1)
        return false;
    x = S.data[S.top--];
    return true;
}

int main()
{
    SqStack S;
    InitStack(S);
    push(S, 1);
    cout << StatckEmpty(S) << endl;
    int prop;
    pop(S,prop);
    cout << "出栈元素：" << prop << endl;
    cout <<"是否为空栈：" << StatckEmpty(S) << endl;
}

