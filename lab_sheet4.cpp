class SinglyLinkedList:
    class Node:
        def _init_(self, data):
            self.data = data
            self.next = None

    def _init_(self):
        self.head = None

    def insert(self, data):
        new_node = self.Node(data)
        if not self.head:
            self.head = new_node
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = new_node

    def delete(self, data):
        if not self.head:
            return
        if self.head.data == data:
            self.head = self.head.next
            return
        current = self.head
        while current.next and current.next.data != data:
            current = current.next
        if current.next:
            current.next = current.next.next

    def traverse(self):
        current = self.head
        result = []
        while current:
            result.append(current.data)
            current = current.next
        return result


class DoublyLinkedList:
    class Node:
        def _init_(self, data):
            self.data = data
            self.prev = None
            self.next = None

    def _init_(self):
        self.head = None

    def insert(self, data):
        new_node = self.Node(data)
        if not self.head:
            self.head = new_node
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = new_node
            new_node.prev = current

    def delete(self, data):
        current = self.head
        while current and current.data != data:
            current = current.next
        if not current:
            return
        if current.prev:
            current.prev.next = current.next
        if current.next:
            current.next.prev = current.prev
        if current == self.head:
            self.head = current.next

    def traverse(self):
        current = self.head
        result = []
        while current:
            result.append(current.data)
            current = current.next
        return result


class CircularLinkedList:
    class Node:
        def _init_(self, data):
            self.data = data
            self.next = None

    def _init_(self):
        self.head = None

    def insert(self, data):
        new_node = self.Node(data)
        if not self.head:
            self.head = new_node
            self.head.next = self.head
        else:
            current = self.head
            while current.next != self.head:
                current = current.next
            current.next = new_node
            new_node.next = self.head

    def traverse(self):
        if not self.head:
            return []
        result = []
        current = self.head
        while True:
            result.append(current.data)
            current = current.next
            if current == self.head:
                break
        return result


class PostfixCalculator:
    def evaluate(self, expression):
        stack = []
        for token in expression.split():
            if token.isdigit():
                stack.append(int(token))
            else:
                b = stack.pop()
                a = stack.pop()
                if token == '+':
                    stack.append(a + b)
                elif token == '-':
                    stack.append(a - b)
                elif token == '*':
                    stack.append(a * b)
                elif token == '/':
                    stack.append(a // b)
        return stack[0]


from collections import deque

class TicketQueue:
    def _init_(self):
        self.queue = deque()

    def enqueue(self, ticket):
        self.queue.append(ticket)

    def dequeue(self):
        if self.queue:
            return self.queue.popleft()
        return None


import heapq

class PriorityQueue:
    def _init_(self):
        self.heap = []

    def insert(self, priority):
        heapq.heappush(self.heap, priority)

    def remove(self):
        if self.heap:
            return heapq.heappop(self.heap)
        return None


# Example Usage
if _name_ == "_main_":
    # Singly Linked List
    sll = SinglyLinkedList()
    sll.insert(1)
    sll.insert(2)
    sll.delete(1)
    print(sll.traverse())  # [2]

    # Doubly Linked List
    dll = DoublyLinkedList()
    dll.insert(1)
    dll.insert(2)
    dll.delete(2)
    print(dll.traverse())  # [1]

    # Circular Linked List
    cll = CircularLinkedList()
    cll.insert(1)
    cll.insert(2)
    print(cll.traverse())  # [1, 2]

    # Postfix Calculator
    calc = PostfixCalculator()
    print(calc.evaluate("5 1 2 + 4 * + 3 -"))  # 14

    # Ticket Queue
    tq = TicketQueue()
    tq.enqueue("ticket1")
    tq.enqueue("ticket2")
    print(tq.dequeue())  # "ticket1"

    # Priority Queue
    pq = PriorityQueue()
    pq.insert(3)
    pq.insert(1)
    pq.insert(2)
    print(pq.remove())  # 1
