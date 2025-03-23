#include <iostream>
using namespace std;

// 合并两个有序子数组
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // 动态内存分配临时数组
    int* leftArr = new int[n1];
    int* rightArr = new int[n2];

    // 将数据复制到临时数组中
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        rightArr[i] = arr[mid + 1 + i];

    // 合并两个有序数组
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // 将剩余的元素拷贝到原数组
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    // 释放动态分配的内存
    delete[] leftArr;
    delete[] rightArr;
}

// 归并排序主函数
void mergeSort(int arr[], int left, int right) {
    if (left >= right)
        return;  // 递归终止条件

    // 找到中间点
    int mid = left + (right - left) / 2;

    // 递归地对两个子数组进行排序
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    // 合并排序后的两个子数组
    merge(arr, left, mid, right);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = { 38, 27, 43, 3, 9, 82, 10 };
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    printArray(arr, n);

    mergeSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    printArray(arr, n);

    return 0;
}
