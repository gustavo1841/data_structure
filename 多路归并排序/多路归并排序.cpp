#include <iostream>

using namespace std;

const int K = 3;  // K 路归并（可调整）

// **合并 K 路有序数组**
void kWayMerge(int arr[], int left, int mid[], int right, int k) {
    int* temp = new int[right - left + 1]; // 临时数组
    int* indices = new int[k]; // 记录 K 个数组的起始索引
    int segmentSize = (right - left + 1) / k; // 每个子数组的大小
    int minIndex, minValue;

    // 初始化 K 个起始索引
    for (int i = 0; i < k; i++) {
        indices[i] = (i == 0) ? left : mid[i - 1] + 1;
    }

    int tempIndex = 0;

    // K 路归并
    while (true) {
        minIndex = -1;
        minValue = 1e9; // 设定一个足够大的初始值

        // 在 K 路中寻找最小值
        for (int i = 0; i < k; i++) {
            if (indices[i] <= (i == k - 1 ? right : mid[i])) {
                if (arr[indices[i]] < minValue) {
                    minValue = arr[indices[i]];
                    minIndex = i;
                }
            }
        }

        // 如果所有段都处理完了，则终止
        if (minIndex == -1) break;

        // 取出最小值放入 temp，并移动指针
        temp[tempIndex++] = arr[indices[minIndex]];
        indices[minIndex]++;
    }

    // 复制回原数组
    for (int i = 0; i < tempIndex; i++) {
        arr[left + i] = temp[i];
    }

    delete[] temp;
    delete[] indices;
}

// **K 路归并排序**
void kWayMergeSort(int arr[], int left, int right, int k) {
    if (left >= right) return;  // 递归终止条件，确保不会无限递归

    int segmentSize = (right - left + 1) / k; // 每个子数组的大小
    if (segmentSize == 0) {
        // 若 segmentSize 过小，则改用普通归并排序
        k = 2;
        segmentSize = (right - left + 1) / k;
    }

    int* mid = new int[k - 1];

    // 计算 K 个分界点
    for (int i = 0; i < k - 1; i++) {
        mid[i] = left + (i + 1) * segmentSize - 1;
        if (mid[i] >= right) {
            mid[i] = right - 1;
        }
    }

    // 递归排序 K 段
    int start = left;
    for (int i = 0; i < k; i++) {
        int end = (i == k - 1) ? right : mid[i];
        kWayMergeSort(arr, start, end, k);
        start = end + 1;
    }

    // 合并 K 段
    kWayMerge(arr, left, mid, right, k);

    delete[] mid;
}

// **测试代码**
int main() {
    int arr[] = { 10, 3, 7, 8, 15, 2, 9, 1, 5, 12, 14, 6, 4, 11, 13 };
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "排序前：";
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;

    kWayMergeSort(arr, 0, size - 1, K);  // 执行 K 路归并排序

    cout << "排序后：";
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
