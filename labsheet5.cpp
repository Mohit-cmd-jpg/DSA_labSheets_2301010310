#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

class TextEditor {
    string text;                      // To store the current text
    stack<pair<string, pair<int, string>>> undo_stack;  // Stack for undo operations
    stack<pair<string, pair<int, string>>> redo_stack;  // Stack for redo operations
    queue<string> clipboard;          // Queue for clipboard management

public:
    TextEditor() : text("") {}

    // Insert text at a specific position
    void insertText(int position, const string& newText) {
        undo_stack.push({"delete", {position, to_string(newText.size())}});
        redo_stack = stack<pair<string, pair<int, string>>>(); // Clear redo stack
        text.insert(position, newText);
    }

    // Delete text from a specific position
    void deleteText(int position, int length) {
        string deletedText = text.substr(position, length);
        undo_stack.push({"insert", {position, deletedText}});
        redo_stack = stack<pair<string, pair<int, string>>>(); // Clear redo stack
        text.erase(position, length);
    }

    // Undo the last operation
    void undo() {
        if (undo_stack.empty()) {
            cout << "Nothing to undo." << endl;
            return;
        }
        auto lastAction = undo_stack.top();
        undo_stack.pop();

        string action = lastAction.first;
        int position = lastAction.second.first;
        string value = lastAction.second.second;

        if (action == "insert") {
            redo_stack.push({"delete", {position, to_string(value.size())}});
            text.insert(position, value);
        } else if (action == "delete") {
            redo_stack.push({"insert", {position, text.substr(position, stoi(value))}});
            text.erase(position, stoi(value));
        }
    }

    // Redo the last undone operation
    void redo() {
        if (redo_stack.empty()) {
            cout << "Nothing to redo." << endl;
            return;
        }
        auto lastAction = redo_stack.top();
        redo_stack.pop();

        string action = lastAction.first;
        int position = lastAction.second.first;
        string value = lastAction.second.second;

        if (action == "insert") {
            undo_stack.push({"delete", {position, to_string(value.size())}});
            text.insert(position, value);
        } else if (action == "delete") {
            undo_stack.push({"insert", {position, text.substr(position, stoi(value))}});
            text.erase(position, stoi(value));
        }
    }

    // Copy text to clipboard
    void copy(int position, int length) {
        string copiedText = text.substr(position, length);
        clipboard.push(copiedText);
    }

    // Paste text from clipboard to a specific position
    void paste(int position) {
        if (clipboard.empty()) {
            cout << "Clipboard is empty." << endl;
            return;
        }
        string textToPaste = clipboard.front();
        clipboard.pop();
        insertText(position, textToPaste);
    }

    // Display the current text
    void display() const {
        cout << text << endl;
    }
};

// Example Usage
int main() {
    TextEditor editor;

    // Insert Text
    editor.insertText(0, "Hello");
    editor.display();

    // Delete Text
    editor.deleteText(0, 2);
    editor.display();

    // Undo Operation
    editor.undo();
    editor.display();

    // Redo Operation
    editor.redo();
    editor.display();

    // Copy and Paste
    editor.copy(0, 2);
    editor.paste(5);
    editor.display();

    return 0;
}
