#include <iostream>

using namespace std;

// **最大堆调整（保持堆的性质）**
void heapify(int arr[], int n, int i) {
    int largest = i;  // 设当前父节点为最大值
    int left = 2 * i + 1;  // 左子节点
    int right = 2 * i + 2; // 右子节点

    // **如果左子节点更大，则更新最大值索引**
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // **如果右子节点更大，则更新最大值索引**
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // **如果最大值索引不是当前父节点，则交换，并递归调整**
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);  // 递归调整子树
    }
}

// **构建最大堆**
void buildMaxHeap(int arr[], int n) {
    // **从最后一个非叶子节点开始**
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// **堆排序**
void heapSort(int arr[], int n) {
    buildMaxHeap(arr, n);  // **1. 先构建最大堆**

    // **2. 依次取出堆顶元素，并调整堆**
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);  // **交换堆顶（最大值）和末尾元素**
        heapify(arr, i, 0);     // **调整剩余元素为最大堆**
    }
}

// **测试代码**
int main() {
    int arr[] = { 4, 10, 3, 5, 1, 8, 6 };
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "排序前：";
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;

    heapSort(arr, size);  // 执行堆排序

    cout << "排序后：";
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
