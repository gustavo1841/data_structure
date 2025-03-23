#include <iostream>

using namespace std;

// **交换两个数**
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// **选择排序**
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;  // 记录最小值索引

        // **寻找当前未排序部分中的最小值**
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // **交换最小值和当前未排序的起始位置**
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

// **测试代码**
int main() {
    int arr[] = { 64, 25, 12, 22, 11 };
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "排序前：";
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;

    selectionSort(arr, size);  // 执行选择排序

    cout << "排序后：";
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
