import tkinter as tk
from tkinter import messagebox
import heapq


class AVLTree:
    class Node:
        def _init_(self, key):
            self.key = key
            self.left = None
            self.right = None
            self.height = 1

    def _init_(self):
        self.root = None

    def insert(self, root, key):
        if not root:
            return self.Node(key)
        elif key < root.key:
            root.left = self.insert(root.left, key)
        else:
            root.right = self.insert(root.right, key)

        root.height = 1 + max(self.get_height(root.left), self.get_height(root.right))
        balance = self.get_balance(root)

        # Rotate to balance the tree
        if balance > 1 and key < root.left.key:
            return self.right_rotate(root)
        if balance < -1 and key > root.right.key:
            return self.left_rotate(root)
        if balance > 1 and key > root.left.key:
            root.left = self.left_rotate(root.left)
            return self.right_rotate(root)
        if balance < -1 and key < root.right.key:
            root.right = self.right_rotate(root.right)
            return self.left_rotate(root)

        return root

    def inorder(self, root):
        return self.inorder(root.left) + [root.key] + self.inorder(root.right) if root else []

    def get_height(self, root):
        return root.height if root else 0

    def get_balance(self, root):
        return self.get_height(root.left) - self.get_height(root.right) if root else 0

    def left_rotate(self, z):
        y = z.right
        T2 = y.left
        y.left = z
        z.right = T2
        z.height = 1 + max(self.get_height(z.left), self.get_height(z.right))
        y.height = 1 + max(self.get_height(y.left), self.get_height(y.right))
        return y

    def right_rotate(self, z):
        y = z.left
        T3 = y.right
        y.right = z
        z.left = T3
        z.height = 1 + max(self.get_height(z.left), self.get_height(z.right))
        y.height = 1 + max(self.get_height(y.left), self.get_height(y.right))
        return y


class Graph:
    def _init_(self):
        self.graph = {}

    def add_edge(self, u, v, weight=1):
        if u not in self.graph:
            self.graph[u] = []
        if v not in self.graph:
            self.graph[v] = []
        self.graph[u].append((v, weight))
        self.graph[v].append((u, weight))

    def bfs(self, start):
        visited = []
        queue = [start]
        while queue:
            node = queue.pop(0)
            if node not in visited:
                visited.append(node)
                queue.extend(neigh[0] for neigh in self.graph[node])
        return visited

    def dijkstra(self, start):
        distances = {node: float('infinity') for node in self.graph}
        distances[start] = 0
        pq = [(0, start)]
        while pq:
            current_distance, current_node = heapq.heappop(pq)
            if current_distance > distances[current_node]:
                continue
            for neighbor, weight in self.graph[current_node]:
                distance = current_distance + weight
                if distance < distances[neighbor]:
                    distances[neighbor] = distance
                    heapq.heappush(pq, (distance, neighbor))
        return distances


class DisasterResponseSystem:
    def _init_(self):
        self.tree = AVLTree()
        self.graph = Graph()
        self.tree_root = None
        self.window = tk.Tk()
        self.window.title("Disaster Response Management System")
        self.create_ui()

    def create_ui(self):
        tk.Label(self.window, text="Tree Operations").grid(row=0, column=0)
        tk.Button(self.window, text="Add Affected Area", command=self.add_area).grid(row=1, column=0)
        tk.Button(self.window, text="Show Areas (In-order)", command=self.show_areas).grid(row=2, column=0)

        tk.Label(self.window, text="Graph Operations").grid(row=0, column=1)
        tk.Button(self.window, text="Add Route", command=self.add_route).grid(row=1, column=1)
        tk.Button(self.window, text="Find BFS Path", command=self.find_bfs).grid(row=2, column=1)
        tk.Button(self.window, text="Find Shortest Path (Dijkstra)", command=self.find_shortest_path).grid(row=3, column=1)

    def add_area(self):
        key = input("Enter area name: ")
        self.tree_root = self.tree.insert(self.tree_root, key)
        messagebox.showinfo("AVL Tree", f"Area {key} added!")

    def show_areas(self):
        areas = self.tree.inorder(self.tree_root)
        messagebox.showinfo("In-order Traversal", f"Affected Areas: {areas}")

    def add_route(self):
        u = input("Enter starting area: ")
        v = input("Enter destination area: ")
        weight = int(input("Enter distance: "))
        self.graph.add_edge(u, v, weight)
        messagebox.showinfo("Graph", f"Route {u} -> {v} with distance {weight} added!")

    def find_bfs(self):
        start = input("Enter starting area: ")
        path = self.graph.bfs(start)
        messagebox.showinfo("BFS", f"Path: {path}")

    def find_shortest_path(self):
        start = input("Enter starting area: ")
        distances = self.graph.dijkstra(start)
        messagebox.showinfo("Dijkstra's", f"Shortest paths: {distances}")

    def run(self):
        self.window.mainloop()


if _name_ == "_main_":
    system = DisasterResponseSystem()
    system.run()
