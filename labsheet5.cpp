from queue import Queue

class TextEditor:
    def _init_(self):
        self.text = []  # Array to store characters
        self.undo_stack = []  # Stack for undo operations
        self.redo_stack = []  # Stack for redo operations
        self.clipboard = Queue()  # Queue for clipboard management

    # Insert text at a specific position
    def insert_text(self, position, text):
        self.undo_stack.append(('delete', position, len(text)))
        self.redo_stack.clear()
        self.text = self.text[:position] + list(text) + self.text[position:]

    # Delete text from a specific position
    def delete_text(self, position, length):
        deleted_text = ''.join(self.text[position:position + length])
        self.undo_stack.append(('insert', position, deleted_text))
        self.redo_stack.clear()
        self.text = self.text[:position] + self.text[position + length:]

    # Undo the last operation
    def undo(self):
        if not self.undo_stack:
            print("Nothing to undo.")
            return
        action, position, value = self.undo_stack.pop()
        if action == 'insert':
            self.redo_stack.append(('delete', position, len(value)))
            self.text = self.text[:position] + list(value) + self.text[position:]
        elif action == 'delete':
            self.redo_stack.append(('insert', position, ''.join(self.text[position:position + value])))
            self.text = self.text[:position] + self.text[position + value:]

    # Redo the last undone operation
    def redo(self):
        if not self.redo_stack:
            print("Nothing to redo.")
            return
        action, position, value = self.redo_stack.pop()
        if action == 'insert':
            self.undo_stack.append(('delete', position, len(value)))
            self.text = self.text[:position] + list(value) + self.text[position:]
        elif action == 'delete':
            self.undo_stack.append(('insert', position, ''.join(self.text[position:position + value])))
            self.text = self.text[:position] + self.text[position + value:]

    # Copy text to clipboard
    def copy(self, position, length):
        copied_text = ''.join(self.text[position:position + length])
        self.clipboard.put(copied_text)

    # Paste text from clipboard to a specific position
    def paste(self, position):
        if self.clipboard.empty():
            print("Clipboard is empty.")
            return
        text_to_paste = self.clipboard.get()
        self.insert_text(position, text_to_paste)

    # Display the current text
    def display(self):
        print(''.join(self.text))


# Example Usage
editor = TextEditor()

# Insert Text
editor.insert_text(0, "Hello")
editor.display()

# Delete Text
editor.delete_text(0, 2)
editor.display()

# Undo Operation
editor.undo()
editor.display()

# Redo Operation
editor.redo()
editor.display()

# Copy and Paste
editor.copy(0, 2)
editor.paste(5)
editor.display()
