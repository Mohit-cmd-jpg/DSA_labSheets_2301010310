#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// Static Array Implementation
class StaticArray {
private:
    int *array;
    int size, count;

public:
    StaticArray(int size) {
        this->size = size;
        array = new int[size];
        count = 0;
    }

    void insert(int value) {
        if (count < size) {
            array[count++] = value;
        } else {
            cout << "Array is full\n";
        }
    }

    void remove(int index) {
        if (index >= 0 && index < count) {
            for (int i = index; i < count - 1; ++i) {
                array[i] = array[i + 1];
            }
            count--;
        } else {
            cout << "Invalid index\n";
        }
    }

    void traverse() {
        for (int i = 0; i < count; ++i) {
            cout << array[i] << " ";
        }
        cout << endl;
    }

    ~StaticArray() {
        delete[] array;
    }
};

// Dynamic Array Implementation
class DynamicArray {
private:
    vector<int> array;

public:
    void insert(int value) {
        array.push_back(value);
    }

    void remove(int index) {
        if (index >= 0 && index < array.size()) {
            array.erase(array.begin() + index);
        } else {
            cout << "Invalid index\n";
        }
    }

    void traverse() {
        for (int val : array) {
            cout << val << " ";
        }
        cout << endl;
    }
};

// String Operations
class StringOperations {
public:
    static string concatenate(const string &str1, const string &str2) {
        return str1 + str2;
    }

    static string substring(const string &s, int start, int end) {
        return s.substr(start, end - start);
    }

    static bool compare(const string &str1, const string &str2) {
        return str1 == str2;
    }

    static unordered_map<char, int> characterFrequency(const string &s) {
        unordered_map<char, int> frequency;
        for (char c : s) {
            frequency[c]++;
        }
        return frequency;
    }
};

// Main Function
int main() {
    // Static Array Example
    cout << "Static Array Example:\n";
    StaticArray sArray(5);
    sArray.insert(1);
    sArray.insert(2);
    sArray.insert(3);
    cout << "Static Array Traversal: ";
    sArray.traverse();
    sArray.remove(1);
    cout << "After Deletion: ";
    sArray.traverse();

    // Dynamic Array Example
    cout << "\nDynamic Array Example:\n";
    DynamicArray dArray;
    dArray.insert(4);
    dArray.insert(5);
    cout << "Dynamic Array Traversal: ";
    dArray.traverse();
    dArray.remove(0);
    cout << "After Deletion: ";
    dArray.traverse();

    // String Operations Example
    cout << "\nString Operations Example:\n";
    string str1 = "hello", str2 = "world";
    cout << "Concatenation: " << StringOperations::concatenate(str1, str2) << endl;
    cout << "Substring: " << StringOperations::substring(str1, 1, 4) << endl;
    cout << "Comparison: " << (StringOperations::compare(str1, str2) ? "Equal" : "Not Equal") << endl;

    unordered_map<char, int> freq = StringOperations::characterFrequency("hello");
    cout << "Character Frequency:\n";
    for (auto &pair : freq) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}
 
