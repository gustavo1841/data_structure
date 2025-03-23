#include <iostream>

using namespace std;

// 冒泡排序
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false; // 标记是否发生了交换
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) { // 交换相邻元素
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // 若没有发生交换，说明已排序完成，提前结束
    }
}

// 输出数组
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "原始数组: ";
    printArray(arr, n);

    bubbleSort(arr, n);

    cout << "排序后的数组: ";
    printArray(arr, n);

    return 0;
}
