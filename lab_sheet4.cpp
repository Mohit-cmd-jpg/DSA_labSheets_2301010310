#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <sstream>
using namespace std;

// Singly Linked List
class SinglyLinkedList {
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };

    Node* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    void insert(int data) {
        Node* new_node = new Node(data);
        if (!head) {
            head = new_node;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = new_node;
        }
    }

    void remove(int data) {
        if (!head) return;
        if (head->data == data) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node* current = head;
        while (current->next && current->next->data != data) {
            current = current->next;
        }
        if (current->next) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    vector<int> traverse() {
        vector<int> result;
        Node* current = head;
        while (current) {
            result.push_back(current->data);
            current = current->next;
        }
        return result;
    }
};

// Doubly Linked List
class DoublyLinkedList {
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node* head;

public:
    DoublyLinkedList() : head(nullptr) {}

    void insert(int data) {
        Node* new_node = new Node(data);
        if (!head) {
            head = new_node;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = new_node;
            new_node->prev = current;
        }
    }

    void remove(int data) {
        Node* current = head;
        while (current && current->data != data) {
            current = current->next;
        }
        if (!current) return;
        if (current->prev) {
            current->prev->next = current->next;
        }
        if (current->next) {
            current->next->prev = current->prev;
        }
        if (current == head) {
            head = current->next;
        }
        delete current;
    }

    vector<int> traverse() {
        vector<int> result;
        Node* current = head;
        while (current) {
            result.push_back(current->data);
            current = current->next;
        }
        return result;
    }
};

// Circular Linked List
class CircularLinkedList {
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };

    Node* head;

public:
    CircularLinkedList() : head(nullptr) {}

    void insert(int data) {
        Node* new_node = new Node(data);
        if (!head) {
            head = new_node;
            head->next = head;
        } else {
            Node* current = head;
            while (current->next != head) {
                current = current->next;
            }
            current->next = new_node;
            new_node->next = head;
        }
    }

    vector<int> traverse() {
        vector<int> result;
        if (!head) return result;
        Node* current = head;
        do {
            result.push_back(current->data);
            current = current->next;
        } while (current != head);
        return result;
    }
};

// Postfix Calculator
class PostfixCalculator {
public:
    int evaluate(const string& expression) {
        vector<int> stack;
        stringstream ss(expression);
        string token;

        while (ss >> token) {
            if (isdigit(token[0])) {
                stack.push_back(stoi(token));
            } else {
                int b = stack.back(); stack.pop_back();
                int a = stack.back(); stack.pop_back();
                if (token == "+") stack.push_back(a + b);
                else if (token == "-") stack.push_back(a - b);
                else if (token == "*") stack.push_back(a * b);
                else if (token == "/") stack.push_back(a / b);
            }
        }
        return stack.back();
    }
};

// Ticket Queue
class TicketQueue {
    deque<string> queue;

public:
    void enqueue(const string& ticket) {
        queue.push_back(ticket);
    }

    string dequeue() {
        if (!queue.empty()) {
            string ticket = queue.front();
            queue.pop_front();
            return ticket;
        }
        return "";
    }
};

// Priority Queue
class PriorityQueue {
    priority_queue<int, vector<int>, greater<int>> heap;

public:
    void insert(int priority) {
        heap.push(priority);
    }

    int remove() {
        if (!heap.empty()) {
            int priority = heap.top();
            heap.pop();
            return priority;
        }
        return -1;
    }
};

// Main Function
int main() {
    // Singly Linked List
    SinglyLinkedList sll;
    sll.insert(1);
    sll.insert(2);
    sll.remove(1);
    for (int val : sll.traverse()) {
        cout << val << " ";
    }
    cout << endl;

    // Doubly Linked List
    DoublyLinkedList dll;
    dll.insert(1);
    dll.insert(2);
    dll.remove(2);
    for (int val : dll.traverse()) {
        cout << val << " ";
    }
    cout << endl;

    // Circular Linked List
    CircularLinkedList cll;
    cll.insert(1);
    cll.insert(2);
    for (int val : cll.traverse()) {
        cout << val << " ";
    }
    cout << endl;

    // Postfix Calculator
    PostfixCalculator calc;
    cout << calc.evaluate("5 1 2 + 4 * + 3 -") << endl;

    // Ticket Queue
    TicketQueue tq;
    tq.enqueue("ticket1");
    tq.enqueue("ticket2");
    cout << tq.dequeue() << endl;

    // Priority Queue
    PriorityQueue pq;
    pq.insert(3);
    pq.insert(1);
    pq.insert(2);
    cout << pq.remove() << endl;

    return 0;
}
