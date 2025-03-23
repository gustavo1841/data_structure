#include <iostream>
using namespace std;

void insertionSort(int arr[], int n) {
    // 从第二个元素开始，假设第一个元素已经排好序
    for (int i = 1; i < n; i++) {
        int key = arr[i];  // 当前要插入的元素
        int j = i - 1;

        // 找到插入位置，右侧元素向右移动
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        // 将当前元素插入到正确的位置
        arr[j + 1] = key;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = { 12, 11, 13, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    printArray(arr, n);

    insertionSort(arr, n);

    cout << "Sorted array: ";
    printArray(arr, n);

    return 0;
}