#include <iostream>

using namespace std;

// 定义最小堆节点结构
struct MinHeapNode {
    int value;  // 存储当前值
    int index;  // 该值所在的原数组索引
    int nextPos; // 该值在对应数组中的下一个位置索引
};

// **小根堆调整函数（堆化）**
void heapify(MinHeapNode heap[], int size, int root) {
    int smallest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < size && heap[left].value < heap[smallest].value)
        smallest = left;
    if (right < size && heap[right].value < heap[smallest].value)
        smallest = right;

    if (smallest != root) {
        swap(heap[root], heap[smallest]);
        heapify(heap, size, smallest);
    }
}

// **K 路归并排序（基于最小堆）**
void kWayMergeSort(int arr[], int left, int right, int k) {
    if (left >= right) return; // 递归终止

    int size = right - left + 1;
    int segmentSize = size / k;
    if (segmentSize == 0) { k = 2; segmentSize = size / k; } // 限制 K 值，防止分块过小

    int* mid = new int[k - 1];

    // 计算 K 个子数组的分界点
    for (int i = 0; i < k - 1; i++) {
        mid[i] = left + (i + 1) * segmentSize - 1;
        if (mid[i] >= right) mid[i] = right - 1;
    }

    // 递归排序 K 个子数组
    int start = left;
    for (int i = 0; i < k; i++) {
        int end = (i == k - 1) ? right : mid[i];
        kWayMergeSort(arr, start, end, k);
        start = end + 1;
    }

    // **使用最小堆进行 K 路归并**
    MinHeapNode* heap = new MinHeapNode[k];
    int* indices = new int[k]; // 记录 K 个子数组的起始索引

    // 初始化最小堆
    for (int i = 0; i < k; i++) {
        indices[i] = (i == 0) ? left : mid[i - 1] + 1;
        heap[i] = { arr[indices[i]], i, indices[i] + 1 };
    }

    // 构建初始最小堆
    for (int i = k / 2 - 1; i >= 0; i--)
        heapify(heap, k, i);

    // 归并排序
    int tempIndex = 0;
    int* temp = new int[size];

    while (true) {
        // 取出堆顶元素（最小值）
        MinHeapNode root = heap[0];
        temp[tempIndex++] = root.value;

        // 移动索引
        if (root.nextPos <= (root.index == k - 1 ? right : mid[root.index])) {
            heap[0] = { arr[root.nextPos], root.index, root.nextPos + 1 };
        }
        else {
            // 若当前数组已经用完，则用 INT_MAX 代替
            heap[0] = { INT_MAX, -1, -1 };
        }

        // 重新堆化
        heapify(heap, k, 0);

        // 结束条件：所有数据归并完
        if (heap[0].value == INT_MAX) break;
    }

    // 复制回原数组
    for (int i = 0; i < size; i++) {
        arr[left + i] = temp[i];
    }

    // 释放内存
    delete[] heap;
    delete[] indices;
    delete[] temp;
    delete[] mid;
}

// **测试代码**
int main() {
    int arr[] = { 10, 3, 7, 8, 15, 2, 9, 1, 5, 12, 14, 6, 4, 11, 13 };
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "排序前：";
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;

    kWayMergeSort(arr, 0, size - 1, 3); // K = 3 进行 K 路归并排序

    cout << "排序后：";
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
