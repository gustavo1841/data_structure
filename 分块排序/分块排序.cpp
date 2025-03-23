#include <iostream>

using namespace std;

// **交换函数**
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// **插入排序（用于小块排序）**
void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;

        // 移动元素找到插入位置
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// **合并两个有序块**
void merge(int arr[], int left[], int leftSize, int right[], int rightSize) {
    int i = 0, j = 0, k = 0;

    // 归并两个有序数组
    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        }
        else {
            arr[k++] = right[j++];
        }
    }

    // 复制剩余元素
    while (i < leftSize) arr[k++] = left[i++];
    while (j < rightSize) arr[k++] = right[j++];
}

// **分块排序（模拟大数据排序）**
void blockSort(int arr[], int size, int blockSize) {
    int numBlocks = (size + blockSize - 1) / blockSize;  // 计算需要多少块

    // **第一步：对每个块进行排序**
    for (int i = 0; i < numBlocks; i++) {
        int start = i * blockSize;
        int end = (start + blockSize < size) ? (start + blockSize) : size;
        insertionSort(arr + start, end - start);  // 对块进行插入排序
    }

    // **第二步：归并已排序的块**
    int* temp = new int[size];
    for (int i = 1; i < numBlocks; i++) {
        int leftSize = i * blockSize;
        int rightSize = (i + 1) * blockSize > size ? size - leftSize : blockSize;

        // 归并当前块与已合并部分
        merge(temp, arr, leftSize, arr + leftSize, rightSize);

        // 复制回原数组
        for (int j = 0; j < leftSize + rightSize; j++) {
            arr[j] = temp[j];
        }
    }

    delete[] temp;
}

// **测试代码**
int main() {
    int arr[] = { 20, 5, 12, 8, 15, 7, 3, 9, 1, 6, 17, 11 };
    int size = sizeof(arr) / sizeof(arr[0]);
    int blockSize = 4;  // 设定块大小（内存限制）

    cout << "排序前：";
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;

    blockSort(arr, size, blockSize);  // 执行分块排序

    cout << "排序后：";
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}