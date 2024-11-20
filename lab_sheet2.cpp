#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Class for 2D Array Operations
class TwoDimensionalArray {
private:
    vector<vector<int>> matrix;

public:
    void insertRow(vector<int> row) {
        matrix.push_back(row);
    }

    void insertColumn(vector<int> column) {
        if (matrix.empty()) {
            for (int value : column) {
                matrix.push_back({value});
            }
        } else {
            for (size_t i = 0; i < matrix.size() && i < column.size(); ++i) {
                matrix[i].push_back(column[i]);
            }
        }
    }

    void deleteRow(int index) {
        if (index >= 0 && index < matrix.size()) {
            matrix.erase(matrix.begin() + index);
        } else {
            cout << "Invalid row index\n";
        }
    }

    void traverse() {
        for (const auto& row : matrix) {
            for (int value : row) {
                cout << value << " ";
            }
            cout << endl;
        }
    }

    vector<vector<int>> transposeMatrix() {
        if (matrix.empty()) return {};
        size_t rows = matrix.size(), cols = matrix[0].size();
        vector<vector<int>> transpose(cols, vector<int>(rows));
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                transpose[j][i] = matrix[i][j];
            }
        }
        return transpose;
    }
};

// String Algorithms
class StringAlgorithms {
public:
    static vector<int> computeLPS(const string& pattern) {
        size_t m = pattern.size();
        vector<int> lps(m, 0);
        int length = 0;
        for (size_t i = 1; i < m;) {
            if (pattern[i] == pattern[length]) {
                lps[i++] = ++length;
            } else if (length) {
                length = lps[length - 1];
            } else {
                lps[i++] = 0;
            }
        }
        return lps;
    }

    static int knuthMorrisPratt(const string& text, const string& pattern) {
        vector<int> lps = computeLPS(pattern);
        size_t n = text.size(), m = pattern.size();
        size_t i = 0, j = 0;
        while (i < n) {
            if (text[i] == pattern[j]) {
                ++i;
                ++j;
                if (j == m) return i - j; // Pattern found
            } else if (j) {
                j = lps[j - 1];
            } else {
                ++i;
            }
        }
        return -1; // Pattern not found
    }

    static string runLengthEncoding(const string& str) {
        string encoded = "";
        size_t count = 1;
        for (size_t i = 1; i <= str.size(); ++i) {
            if (i < str.size() && str[i] == str[i - 1]) {
                ++count;
            } else {
                encoded += to_string(count) + str[i - 1];
                count = 1;
            }
        }
        return encoded;
    }
};

// Main Function
int main() {
    // 2D Array Example
    cout << "2D Array Operations Example:\n";
    TwoDimensionalArray tdArray;
    tdArray.insertRow({1, 2});
    tdArray.insertColumn({3, 4});
    cout << "2D Array Traversal:\n";
    tdArray.traverse();
    tdArray.deleteRow(0);
    cout << "After Deleting Row:\n";
    tdArray.traverse();

    vector<vector<int>> transpose = tdArray.transposeMatrix();
    cout << "Transpose of the Matrix:\n";
    for (const auto& row : transpose) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }

    // String Pattern Matching Example
    cout << "\nString Pattern Matching Example:\n";
    string text = "abxabcabcaby", pattern = "abcaby";
    int index = StringAlgorithms::knuthMorrisPratt(text, pattern);
    if (index != -1) {
        cout << "Pattern found at index: " << index << endl;
    } else {
        cout << "Pattern not found\n";
    }

    // Run Length Encoding Example
    cout << "\nRun Length Encoding Example:\n";
    string str = "aaabbbcccaaa";
    string encoded = StringAlgorithms::runLengthEncoding(str);
    cout << "Encoded String: " << encoded << endl;

    return 0;
}

