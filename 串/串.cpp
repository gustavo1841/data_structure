
#include <iostream>
using namespace std;
#define MAXLEN 255
//长顺序存储
typedef struct {
    char ch[MAXLEN];
    int length;
}StringPlus;
//堆分配存储
typedef struct {
    char* ch;
    int length;

}HeapString;
/**
从主串S的第一字符起，与字符串T的第一个字符比较,若相等，则继续逐个比较后续的字符；
否则从主串的下一个字符起，重新和T的字符比较；以此类推，直至字符串T中的每个字符依次和主串S中的一个连续的字符序列相等，则称匹配成功，
函数数值为与T中的第一个字符相等的字符在主串S中的序号。否则称匹配不成功，函数值为0
**/

int index(StringPlus s,StringPlus t) {
    int i = 1, j = 1;
    while (i<=s.length && j<=t.length) {
        if (s.ch[i]==t.ch[j]) {
            ++i;++j;
        }
        else {
            //指针后退重新开始匹配
            i = i - j + 2;
            j = 1;
        }
        if (j>t.length) {
            return i - t.length;
        }
        else {
            return 0;
        }
    }
}

int kmpIndex(StringPlus s,StringPlus t,int next[]) {
    int i = 1, j = 1;
    while (i <= s.length && j<=t.length) {
        if (j==0 || s.ch[i]==t.ch[j]) {
            ++i;++j;//继续比较后面的字符
        }
        else {
            j = next[j];//模式串向右移动
        }
        if (j>t.length) {
            return i - t.length; //匹配成功
        }
        else {
            return 0;
        }
    }
}

int main()
{
}


