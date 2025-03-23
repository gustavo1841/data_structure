#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// 哈夫曼树的节点结构
struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left, * right;

    HuffmanNode(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}
};

// 优先队列的比较函数
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq; // 小顶堆
    }
};

// 递归构建哈夫曼编码
void generateHuffmanCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCodes[root->ch] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// 构造哈夫曼树并生成编码
unordered_map<char, string> buildHuffmanTree(const unordered_map<char, int>& freqMap) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    // 1. 初始化最小堆
    for (auto pair : freqMap) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    // 2. 构造哈夫曼树
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        HuffmanNode* newNode = new HuffmanNode('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }

    // 3. 生成哈夫曼编码
    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(pq.top(), "", huffmanCodes);

    return huffmanCodes;
}

int main() {
    unordered_map<char, int> freqMap = {
        {'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}
    };

    unordered_map<char, string> huffmanCodes = buildHuffmanTree(freqMap);

    // 输出哈夫曼编码
    for (auto pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}
