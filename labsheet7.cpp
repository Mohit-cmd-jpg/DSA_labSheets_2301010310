#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <climits>
#include <algorithm>

using namespace std;

// AVL Tree Implementation
class AVLTree {
public:
    struct Node {
        string key;
        Node* left;
        Node* right;
        int height;

        Node(string k) : key(k), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    AVLTree() : root(nullptr) {}

    Node* insert(Node* root, string key) {
        if (root == nullptr) {
            return new Node(key);
        }

        if (key < root->key) {
            root->left = insert(root->left, key);
        } else {
            root->right = insert(root->right, key);
        }

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        int balance = getBalance(root);

        // Balancing the tree
        if (balance > 1 && key < root->left->key) {
            return rightRotate(root);
        }
        if (balance < -1 && key > root->right->key) {
            return leftRotate(root);
        }
        if (balance > 1 && key > root->left->key) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && key < root->right->key) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    vector<string> inorder(Node* root) {
        vector<string> result;
        if (root) {
            auto left = inorder(root->left);
            result.insert(result.end(), left.begin(), left.end());
            result.push_back(root->key);
            auto right = inorder(root->right);
            result.insert(result.end(), right.begin(), right.end());
        }
        return result;
    }

private:
    int getHeight(Node* root) {
        return root ? root->height : 0;
    }

    int getBalance(Node* root) {
        return root ? getHeight(root->left) - getHeight(root->right) : 0;
    }

    Node* leftRotate(Node* z) {
        Node* y = z->right;
        Node* T2 = y->left;

        y->left = z;
        z->right = T2;

        z->height = 1 + max(getHeight(z->left), getHeight(z->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    Node* rightRotate(Node* z) {
        Node* y = z->left;
        Node* T3 = y->right;

        y->right = z;
        z->left = T3;

        z->height = 1 + max(getHeight(z->left), getHeight(z->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }
};

// Graph Implementation
class Graph {
    map<string, vector<pair<string, int>>> adjList;

public:
    void addEdge(string u, string v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
    }

    vector<string> bfs(string start) {
        vector<string> visited;
        set<string> visitedSet;
        queue<string> q;

        q.push(start);

        while (!q.empty()) {
            string node = q.front();
            q.pop();

            if (visitedSet.find(node) == visitedSet.end()) {
                visited.push_back(node);
                visitedSet.insert(node);

                for (auto& neighbor : adjList[node]) {
                    q.push(neighbor.first);
                }
            }
        }

        return visited;
    }

    map<string, int> dijkstra(string start) {
        map<string, int> distances;
        for (auto& pair : adjList) {
            distances[pair.first] = INT_MAX;
        }
        distances[start] = 0;

        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int currentDistance = pq.top().first;
            string currentNode = pq.top().second;
            pq.pop();

            if (currentDistance > distances[currentNode]) {
                continue;
            }

            for (auto& neighbor : adjList[currentNode]) {
                int distance = currentDistance + neighbor.second;

                if (distance < distances[neighbor.first]) {
                    distances[neighbor.first] = distance;
                    pq.push({distance, neighbor.first});
                }
            }
        }

        return distances;
    }
};

// Main DisasterResponseSystem
class DisasterResponseSystem {
    AVLTree tree;
    Graph graph;

public:
    void run() {
        while (true) {
            cout << "\nMenu:\n"
                 << "1. Add Affected Area\n"
                 << "2. Show Affected Areas (In-order)\n"
                 << "3. Add Route\n"
                 << "4. Find BFS Path\n"
                 << "5. Find Shortest Path (Dijkstra)\n"
                 << "6. Exit\n"
                 << "Enter your choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
            case 1:
                addArea();
                break;
            case 2:
                showAreas();
                break;
            case 3:
                addRoute();
                break;
            case 4:
                findBFS();
                break;
            case 5:
                findShortestPath();
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice! Try again.\n";
            }
        }
    }

private:
    void addArea() {
        cout << "Enter area name: ";
        string area;
        cin >> area;
        tree.root = tree.insert(tree.root, area);
        cout << "Area " << area << " added!\n";
    }

    void showAreas() {
        auto areas = tree.inorder(tree.root);
        cout << "Affected Areas (In-order): ";
        for (const string& area : areas) {
            cout << area << " ";
        }
        cout << endl;
    }

    void addRoute() {
        cout << "Enter starting area: ";
        string u;
        cin >> u;
        cout << "Enter destination area: ";
        string v;
        cin >> v;
        cout << "Enter distance: ";
        int weight;
        cin >> weight;
        graph.addEdge(u, v, weight);
        cout << "Route " << u << " -> " << v << " with distance " << weight << " added!\n";
    }

    void findBFS() {
        cout << "Enter starting area: ";
        string start;
        cin >> start;
        auto path = graph.bfs(start);
        cout << "BFS Path: ";
        for (const string& area : path) {
            cout << area << " ";
        }
        cout << endl;
    }

    void findShortestPath() {
        cout << "Enter starting area: ";
        string start;
        cin >> start;
        auto distances = graph.dijkstra(start);
        cout << "Shortest paths:\n";
        for (auto& pair : distances) {
            cout << "To " << pair.first << ": " << pair.second << "\n";
        }
    }
};

// Main Function
int main() {
    DisasterResponseSystem system;
    system.run();
    return 0;
}
