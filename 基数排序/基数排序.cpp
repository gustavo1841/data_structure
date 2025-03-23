#include <iostream>
using namespace std;

// 计数排序，用于按某一位排序
void countingSort(int arr[], int n, int exp) {
    int *output = new int[n];  // 存储排序结果
    int count[10] = { 0 };  // 计数数组，基数排序的基数为10

    // 计算每个数字在该位的出现次数
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    // 计算每个元素的最终位置
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // 构建输出数组
    for (int i = n - 1; i >= 0; i--) {
        int index = (arr[i] / exp) % 10;
        output[count[index] - 1] = arr[i];
        count[index]--;
    }

    // 将输出数组复制到原数组
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// 基数排序主函数
void radixSort(int arr[], int n) {
    // 找到数组中最大值
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    // 从个位开始，一直到最大数的最高位
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSort(arr, n, exp);  // 按当前位进行计数排序
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
    int arr[] = { 170, 45, 75, 90, 802, 24, 2, 66 };
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "原始数组: ";
    printArray(arr, n);

    radixSort(arr, n);

    cout << "排序后的数组: ";
    printArray(arr, n);

    return 0;
}
