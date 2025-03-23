#include <iostream>
using namespace std;
//无序的情况
int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i; // 找到目标值，返回索引
        }
    }
    return -1; // 未找到目标值
}


int main() {
    int arr[] = { 3, 8, 1, 4, 6, 9, 2 };
    int target = 4;
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = linearSearch(arr, n, target);
    if (result != -1) {
        cout << "找到目标值 " << target << "，索引为：" << result << endl;
    }
    else {
        cout << "目标值 " << target << " 不存在" << endl;
    }
    return 0;
}
