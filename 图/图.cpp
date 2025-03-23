#include <iostream>

using namespace std;

// 链表结构，表示邻接表中的节点
struct Node {
    int vertex;   // 目标顶点
    Node* next;   // 指向下一个邻接节点
};

// 图的类
class Graph {
private:
    int V;         // 顶点数
    Node** adjList; // 邻接表，数组中每个元素是指向链表的指针

public:
    // 构造函数
    Graph(int V) {
        this->V = V;
        adjList = new Node * [V]; // 动态分配邻接表
        for (int i = 0; i < V; i++) {
            adjList[i] = nullptr; // 初始化为空
        }
    }

    // 添加边（无向图）
    void addEdge(int v, int w) {
        Node* newNode = new Node{ w, adjList[v] };
        adjList[v] = newNode;

        // 若是无向图，双向添加
        newNode = new Node{ v, adjList[w] };
        adjList[w] = newNode;
    }

    // 深度优先搜索 (DFS)
    void DFS(int start) {
        bool* visited = new bool[V]();
        DFSHelper(start, visited);
        delete[] visited;
    }

private:
    void DFSHelper(int v, bool* visited) {
        visited[v] = true;
        cout << v << " ";

        Node* node = adjList[v];
        while (node) {
            if (!visited[node->vertex]) {
                DFSHelper(node->vertex, visited);
            }
            node = node->next;
        }
    }

public:
    // 广度优先搜索 (BFS)
    void BFS(int start) {
        bool* visited = new bool[V]();
        int* queue = new int[V]; // 队列数组
        int front = 0, rear = 0;

        queue[rear++] = start;
        visited[start] = true;

        while (front < rear) {
            int v = queue[front++];

            cout << v << " ";

            // 遍历邻接表
            Node* node = adjList[v];
            while (node) {
                if (!visited[node->vertex]) {
                    visited[node->vertex] = true;
                    queue[rear++] = node->vertex;
                }
                node = node->next;
            }
        }

        delete[] visited;
        delete[] queue;
    }

    // 析构函数（释放邻接表）
    ~Graph() {
        for (int i = 0; i < V; i++) {
            Node* node = adjList[i];
            while (node) {
                Node* temp = node;
                node = node->next;
                delete temp;
            }
        }
        delete[] adjList;
    }
};

// 主函数
int main() {
    Graph g(6);

    // 添加边
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);

    // 执行 DFS
    cout << "DFS Traversal: ";
    g.DFS(0);
    cout << endl;

    // 执行 BFS
    cout << "BFS Traversal: ";
    g.BFS(0);
    cout << endl;

    return 0;
}
