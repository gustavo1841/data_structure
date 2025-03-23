#include <iostream>
#include <vector>
#include <list>

using namespace std;
//拉链法
class HashTable {
private:
    vector<list<int>> table;
    int size;

    int hash(int key) {
        return key % size;
    }

public:
    HashTable(int s) : size(s) {
        table.resize(size);
    }

    void insert(int key) {
        int index = hash(key);
        table[index].push_back(key);
    }

    bool search(int key) {
        int index = hash(key);
        for (int num : table[index]) {
            if (num == key) return true;
        }
        return false;
    }
};

//开放地址法
class OpenAddressingHashTable {
private:
    vector<int> table;
    int size;
    int EMPTY = -1;

    int hash(int key) {
        return key % size;
    }

public:
    OpenAddressingHashTable(int s) : size(s) {
        table.resize(size, EMPTY);
    }

    void insert(int key) {
        int index = hash(key);
        while (table[index] != EMPTY) {  // 线性探测
            index = (index + 1) % size;
        }
        table[index] = key;
    }

    bool search(int key) {
        int index = hash(key);
        int start = index;
        while (table[index] != EMPTY) {
            if (table[index] == key) return true;
            index = (index + 1) % size;
            if (index == start) break;
        }
        return false;
    }
};


int main() {
    HashTable ht(10);
    ht.insert(15);
    ht.insert(25);
    cout << ht.search(15) << endl; // 输出 1
    cout << ht.search(20) << endl; // 输出 0

    OpenAddressingHashTable oaht(10);
    oaht.insert(15);
    oaht.insert(25);
    cout << oaht.search(15) << endl; // 输出 1
    cout << oaht.search(20) << endl; // 输出 0
}
