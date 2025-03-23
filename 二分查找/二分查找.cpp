#include <iostream>
using namespace std;

int binarySearchIterative(int arr[], int n, int target) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) return mid;
        else if (arr[mid] > target) right = mid - 1;
        else left = mid + 1;
    }

    return -1; // 未找到
}

int main() {
    int arr[] = { 1, 3, 5, 7, 9, 11, 13, 15 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 11;

    int result = binarySearchIterative(arr, n, target);
    if (result != -1)
        cout << "找到目标值 " << target << "，索引为：" << result << endl;
    else
        cout << "目标值 " << target << " 不存在" << endl;

    return 0;
}