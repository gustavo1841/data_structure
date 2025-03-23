#include <iostream>
#include <vector>

class BlockSearch {
private:
    std::vector<int> data;         // 存储所有数据，要求有序
    std::vector<int> index_max;    // 每个块的最大值
    std::vector<int> index_start;  // 每个块的起始索引
    int block_size;                // 每块的大小

public:
    // 构造函数：接受一个有序数组，并构建索引表
    BlockSearch(const std::vector<int>& sorted_data, int block_size) {
        this->data = sorted_data;
        this->block_size = block_size;
        build_index();
    }

    // 构建索引表
    void build_index() {
        int n = data.size();
        int num_blocks = (n + block_size - 1) / block_size; // 计算块数

        for (int i = 0; i < num_blocks; i++) {
            int start_idx = i * block_size;
            int end_idx = std::min(start_idx + block_size, n);
            index_start.push_back(start_idx);  // 记录每个块的起始索引
            index_max.push_back(data[end_idx - 1]); // 记录块的最大值
        }
    }

    // 分块查找
    int search(int target) {
        int num_blocks = index_max.size();

        // 1. 通过索引表找到目标值所在的块
        int block_idx = -1;
        for (int i = 0; i < num_blocks; i++) {
            if (target <= index_max[i]) {
                block_idx = i;
                break;
            }
        }

        // 若所有块的最大值都小于目标值，则目标值不存在
        if (block_idx == -1) return -1;

        // 2. 在对应的块内进行顺序查找
        int start = index_start[block_idx];
        int end = std::min(start + block_size, (int)data.size());

        for (int i = start; i < end; i++) {
            if (data[i] == target) return i; // 找到目标值，返回索引
        }

        return -1; // 没找到
    }

    // 打印索引表（调试用）
    void print_index() {
        std::cout << "索引表：" << std::endl;
        for (size_t i = 0; i < index_start.size(); i++) {
            std::cout << "块 " << i << ": 起始索引 = " << index_start[i]
                << ", 最大值 = " << index_max[i] << std::endl;
        }
    }
};

// 测试代码
int main() {
    std::vector<int> sorted_data = { 1, 3, 5, 7, 9, 12, 14, 18, 21, 25, 30, 35, 40 };
    int block_size = 4;

    BlockSearch bs(sorted_data, block_size);
    bs.print_index();

    int target = 18;
    int index = bs.search(target);

    if (index != -1) {
        std::cout << "元素 " << target << " 在索引 " << index << std::endl;
    }
    else {
        std::cout << "元素 " << target << " 未找到" << std::endl;
    }

    return 0;
}