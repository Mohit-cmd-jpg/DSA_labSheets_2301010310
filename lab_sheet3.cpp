#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

// Array-based Stack Implementation
class ArrayStack {
private:
    int *stack;
    int capacity;
    int top;

public:
    ArrayStack(int size) {
        capacity = size;
        stack = new int[capacity];
        top = -1;
    }

    void push(int value) {
        if (top == capacity - 1) {
            cout << "Stack Overflow\n";
        } else {
            stack[++top] = value;
        }
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
            return -1;
        } else {
            return stack[top--];
        }
    }

    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return -1;
        } else {
            return stack[top];
        }
    }

    bool isEmpty() {
        return top == -1;
    }

    ~ArrayStack() {
        delete[] stack;
    }
};

// Linked List-based Stack Implementation
struct Node {
    int data;
    Node* next;
};

class LinkedListStack {
private:
    Node* top;

public:
    LinkedListStack() {
        top = nullptr;
    }

    void push(int value) {
        Node* newNode = new Node{value, top};
        top = newNode;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
            return -1;
        } else {
            Node* temp = top;
            int value = temp->data;
            top = top->next;
            delete temp;
            return value;
        }
    }

    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return -1;
        } else {
            return top->data;
        }
    }

    bool isEmpty() {
        return top == nullptr;
    }

    ~LinkedListStack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

// Array-based Queue Implementation
class ArrayQueue {
private:
    int *queue;
    int capacity;
    int front, rear, count;

public:
    ArrayQueue(int size) {
        capacity = size;
        queue = new int[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }

    void enqueue(int value) {
        if (count == capacity) {
            cout << "Queue Overflow\n";
        } else {
            rear = (rear + 1) % capacity;
            queue[rear] = value;
            count++;
        }
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow\n";
            return -1;
        } else {
            int value = queue[front];
            front = (front + 1) % capacity;
            count--;
            return value;
        }
    }

    int peek() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return -1;
        } else {
            return queue[front];
        }
    }

    bool isEmpty() {
        return count == 0;
    }

    ~ArrayQueue() {
        delete[] queue;
    }
};

// Linked List-based Queue Implementation
class LinkedListQueue {
private:
    struct Node {
        int data;
        Node* next;
    };

    Node *front, *rear;

public:
    LinkedListQueue() {
        front = rear = nullptr;
    }

    void enqueue(int value) {
        Node* newNode = new Node{value, nullptr};
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow\n";
            return -1;
        } else {
            Node* temp = front;
            int value = temp->data;
            front = front->next;
            if (front == nullptr) rear = nullptr;
            delete temp;
            return value;
        }
    }

    int peek() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return -1;
        } else {
            return front->data;
        }
    }

    bool isEmpty() {
        return front == nullptr;
    }

    ~LinkedListQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

// Reverse a String Using Stack
string reverseString(const string& str) {
    stack<char> s;
    for (char c : str) {
        s.push(c);
    }

    string reversed = "";
    while (!s.empty()) {
        reversed += s.top();
        s.pop();
    }
    return reversed;
}

// Print Queue Simulation
class PrintQueue {
private:
    queue<string> printQueue;

public:
    void addDocument(const string& doc) {
        printQueue.push(doc);
    }

    void processDocument() {
        if (printQueue.empty()) {
            cout << "No documents in the queue\n";
        } else {
            cout << "Printing: " << printQueue.front() << endl;
            printQueue.pop();
        }
    }
};

// Main Function
int main() {
    // Array-based Stack Example
    cout << "Array Stack Example:\n";
    ArrayStack arrayStack(5);
    arrayStack.push(1);
    arrayStack.push(2);
    cout << "Top of Stack: " << arrayStack.peek() << endl;
    cout << "Popped: " << arrayStack.pop() << endl;

    // Linked List-based Queue Example
    cout << "\nLinked List Queue Example:\n";
    LinkedListQueue linkedQueue;
    linkedQueue.enqueue(10);
    linkedQueue.enqueue(20);
    cout << "Front of Queue: " << linkedQueue.peek() << endl;
    cout << "Dequeued: " << linkedQueue.dequeue() << endl;

    // Reverse String Example
    cout << "\nReversing String:\n";
    string input = "hello";
    cout << "Reversed: " << reverseString(input) << endl;

    // Print Queue Example
    cout << "\nPrint Queue Simulation:\n";
    PrintQueue printQueue;
    printQueue.addDocument("doc1");
    printQueue.addDocument("doc2");
    printQueue.processDocument();
    printQueue.processDocument();

    return 0;
}

