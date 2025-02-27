
#include <iostream>
#define InitSize 2
using namespace std;
//定义顺序表的结构
typedef struct {
    int *data;
    int MaxSize,length;
}SqList;
//初始化表
void InitList(SqList &L) {
    L.data = new int[InitSize];
    L.length = 0;
    L.MaxSize = InitSize;
    for (int i = 0;i < InitSize;i++) {
        L.data[i] = NULL;
    }
}

//动态扩容
bool InCreateSize(SqList &L) {
    int* p = L.data;
    int * list = new int[L.length*2];
    for (int i = 0;i < L.length;i++) {
        list[i] = p[i];
    }
    cout << "动态扩容成功！" <<"扩容前容量："<<L.MaxSize<<"，扩容后："<<L.MaxSize*2<< endl;
    L.MaxSize = L.MaxSize * 2;
    L.data = list;
    free(p);
    return true;
}

//顺序表指定位置插入
bool ListInsert(SqList &L,int i,int data) {
    //判断指定插入的位置是否合理
    if (i<1 || i>L.length+1) {
        return false;
    }
    //判断数组长度是否超出最大值
    if (L.length>=L.MaxSize) {
        bool isCreate = InCreateSize(L);
        if (!isCreate)
            return false;
    }
    //所有元素从指定位置往后挪一步，腾出i的位置
    for (int j = L.length;j >= i;j--) {
        L.data[j] = L.data[j - 1];
    }
    L.data[i-1] = data;
    L.length++;
    return true;
}

//顺序表删除
bool ListDelete(SqList &L,int i,int &e) {
    if (i<1 && i>L.length) {
        return false;
    }
    e = L.data[i - 1];
    for (int j = i;j <= L.length;j++) {
        L.data[j - 1] = L.data[j];
    }
    L.length--;
    return true;
}

//按值查找元素位置
int get(SqList &L,int data) {
    for (int i = 0;i < L.length;i++) {
        if (data==L.data[i]) {
            return i + 1;
        }
    }
    return 0;
}
//打印
void printList(SqList L) {
    for (int i = 0;i < L.length;i++) {
        cout << "下标为：" << i<<"：" << L.data[i] << endl;
    }
}

int main()
{
    SqList L;
    InitList(L);
    ListInsert(L, 1, 1);
    ListInsert(L, 2, 2);
    ListInsert(L, 3, 3);
    printList(L);
    int i;
    ListDelete(L, 2, i);
    cout << "删除的元素："<<i << endl;
    cout << "查找元素：" << get(L, 3) << endl;
}
