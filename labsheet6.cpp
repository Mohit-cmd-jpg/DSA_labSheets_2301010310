#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

// Binary Tree Implementation
class BinaryTree {
public:
    struct Node {
        int key;
        Node* left;
        Node* right;
        Node(int value) : key(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    BinaryTree() : root(nullptr) {}

    Node* insert(Node* root, int key) {
        if (root == nullptr) {
            return new Node(key);
        }
        if (key < root->key) {
            root->left = insert(root->left, key);
        } else {
            root->right = insert(root->right, key);
        }
        return root;
    }

    vector<int> inorder(Node* root) {
        vector<int> result;
        if (root) {
            vector<int> left = inorder(root->left);
            result.insert(result.end(), left.begin(), left.end());
            result.push_back(root->key);
            vector<int> right = inorder(root->right);
            result.insert(result.end(), right.begin(), right.end());
        }
        return result;
    }

    vector<int> preorder(Node* root) {
        vector<int> result;
        if (root) {
            result.push_back(root->key);
            vector<int> left = preorder(root->left);
            result.insert(result.end(), left.begin(), left.end());
            vector<int> right = preorder(root->right);
            result.insert(result.end(), right.begin(), right.end());
        }
        return result;
    }

    vector<int> postorder(Node* root) {
        vector<int> result;
        if (root) {
            vector<int> left = postorder(root->left);
            result.insert(result.end(), left.begin(), left.end());
            vector<int> right = postorder(root->right);
            result.insert(result.end(), right.begin(), right.end());
            result.push_back(root->key);
        }
        return result;
    }
};

// Graph Implementation
class Graph {
    map<string, vector<pair<string, int>>> adjList;

public:
    void addEdge(string u, string v, int weight = 1) {
        adjList[u].push_back({v, weight});
    }

    vector<string> bfs(string start) {
        vector<string> visited;
        queue<string> q;
        set<string> visitedSet;

        q.push(start);
        while (!q.empty()) {
            string node = q.front();
            q.pop();
            if (visitedSet.find(node) == visitedSet.end()) {
                visited.push_back(node);
                visitedSet.insert(node);
                for (auto neighbor : adjList[node]) {
                    q.push(neighbor.first);
                }
            }
        }
        return visited;
    }

    vector<string> dfs(string start) {
        vector<string> visited;
        set<string> visitedSet;
        dfsHelper(start, visited, visitedSet);
        return visited;
    }

private:
    void dfsHelper(string node, vector<string>& visited, set<string>& visitedSet) {
        if (visitedSet.find(node) != visitedSet.end()) {
            return;
        }
        visited.push_back(node);
        visitedSet.insert(node);
        for (auto neighbor : adjList[node]) {
            dfsHelper(neighbor.first, visited, visitedSet);
        }
    }
};

// Main Tool
class VisualizationTool {
    BinaryTree tree;
    Graph graph;

public:
    void run() {
        while (true) {
            cout << "\nMenu:\n"
                 << "1. Insert Tree Node\n"
                 << "2. Show Tree In-order Traversal\n"
                 << "3. Add Graph Edge\n"
                 << "4. Show Graph BFS Traversal\n"
                 << "5. Exit\n"
                 << "Enter your choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
            case 1:
                insertTreeNode();
                break;
            case 2:
                showTreeInorder();
                break;
            case 3:
                addGraphEdge();
                break;
            case 4:
                showGraphBFS();
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice! Try again.\n";
            }
        }
    }

private:
    void insertTreeNode() {
        cout << "Enter node value: ";
        int value;
        cin >> value;
        tree.root = tree.insert(tree.root, value);
        cout << "Node " << value << " inserted!\n";
    }

    void showTreeInorder() {
        vector<int> traversal = tree.inorder(tree.root);
        cout << "In-order Traversal: ";
        for (int val : traversal) {
            cout << val << " ";
        }
        cout << endl;
    }

    void addGraphEdge() {
        cout << "Enter starting node: ";
        string u;
        cin >> u;
        cout << "Enter ending node: ";
        string v;
        cin >> v;
        cout << "Enter weight (default 1): ";
        int weight;
        cin >> weight;
        graph.addEdge(u, v, weight);
        cout << "Edge " << u << " -> " << v << " added!\n";
    }

    void showGraphBFS() {
        cout << "Enter starting node for BFS: ";
        string start;
        cin >> start;
        vector<string> traversal = graph.bfs(start);
        cout << "BFS Traversal: ";
        for (const string& node : traversal) {
            cout << node << " ";
        }
        cout << endl;
    }
};

// Main function
int main() {
    VisualizationTool tool;
    tool.run();
    return 0;
}
