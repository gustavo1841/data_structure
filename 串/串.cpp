#include <iostream>

class String {
private:
    char* data;
    size_t length;

    // 私有构造函数：直接使用现有字符数组，避免重复分配
    String(char* buffer, size_t len, bool) : data(buffer), length(len) {}

public:
    // 默认构造函数
    String() : data(new char[1] {'\0'}), length(0) {}

    // 构造函数
    String(const char* str) {
        length = 0;
        while (str[length] != '\0') length++;
        data = new char[length + 1];
        for (size_t i = 0; i < length; i++) {
            data[i] = str[i];
        }
        data[length] = '\0';
    }

    // 拷贝构造函数
    String(const String& other) {
        length = other.length;
        data = new char[length + 1];
        for (size_t i = 0; i < length; i++) {
            data[i] = other.data[i];
        }
        data[length] = '\0';
    }

    // 移动构造函数
    String(String&& other) noexcept : data(other.data), length(other.length) {
        other.data = nullptr;
        other.length = 0;
    }

    // 析构函数
    ~String() {
        delete[] data;
    }

    // 赋值运算符重载（拷贝）
    String& operator=(const String& other) {
        if (this != &other) {
            if (length != other.length) { // 只有在长度不同的时候才重新分配
                delete[] data;
                data = new char[other.length + 1];
            }
            length = other.length;
            for (size_t i = 0; i < length; i++) {
                data[i] = other.data[i];
            }
            data[length] = '\0';
        }
        return *this;
    }

    // 赋值运算符重载（移动）
    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            length = other.length;
            other.data = nullptr;
            other.length = 0;
        }
        return *this;
    }

    // 获取长度
    size_t size() const {
        return length;
    }

    // 串连接 (O(n + m))
    String operator+(const String& other) const {
        char* newData = new char[length + other.length + 1];
        for (size_t i = 0; i < length; i++) {
            newData[i] = data[i];
        }
        for (size_t i = 0; i < other.length; i++) {
            newData[length + i] = other.data[i];
        }
        newData[length + other.length] = '\0';
        return String(newData, length + other.length, true);
    }

    // 子串提取 (O(len))
    String substring(size_t start, size_t len) const {
        if (start >= length) return String("");
        len = (start + len > length) ? (length - start) : len;
        char* subData = new char[len + 1];
        for (size_t i = 0; i < len; i++) {
            subData[i] = data[start + i];
        }
        subData[len] = '\0';
        return String(subData, len, true);
    }

    // 查找是否包含某个子串 (O(n * m))
    bool contains(const String& subStr) const {
        if (subStr.length > length) return false;

        // 遍历当前字符串
        for (size_t i = 0; i <= length - subStr.length; i++) {
            size_t j = 0;
            // 比较子串
            while (j < subStr.length && data[i + j] == subStr.data[j]) {
                j++;
            }
            // 如果完全匹配，返回 true
            if (j == subStr.length) {
                return true;
            }
        }
        return false;
    }

    // 输出流重载
    void print() const {
        for (size_t i = 0; i < length; i++) {
            std::cout << data[i];
        }
        std::cout << std::endl;
    }
};

int main() {
    String s1("Hello");
    String s2("World");
    String s3 = s1 + s2;
    s3.print(); // HelloWorld

    String s4 = s3.substring(5, 5);
    s4.print(); // World

    // 检查是否包含子串
    String sub("World");
    if (s3.contains(sub)) {
        std::cout << "Found substring!" << std::endl; // Found substring!
    }
    else {
        std::cout << "Substring not found." << std::endl;
    }

    return 0;
}
