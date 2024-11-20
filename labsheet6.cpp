import tkinter as tk
from tkinter import messagebox
import networkx as nx
import matplotlib.pyplot as plt


class BinaryTree:
    def _init_(self):
        self.root = None

    class Node:
        def _init_(self, key):
            self.key = key
            self.left = None
            self.right = None

    def insert(self, root, key):
        if root is None:
            return self.Node(key)
        if key < root.key:
            root.left = self.insert(root.left, key)
        else:
            root.right = self.insert(root.right, key)
        return root

    def inorder(self, root):
        if root:
            return self.inorder(root.left) + [root.key] + self.inorder(root.right)
        return []

    def preorder(self, root):
        if root:
            return [root.key] + self.preorder(root.left) + self.preorder(root.right)
        return []

    def postorder(self, root):
        if root:
            return self.postorder(root.left) + self.postorder(root.right) + [root.key]
        return []


class Graph:
    def _init_(self):
        self.graph = {}

    def add_edge(self, u, v, weight=1):
        if u not in self.graph:
            self.graph[u] = []
        self.graph[u].append((v, weight))

    def bfs(self, start):
        visited = []
        queue = [start]

        while queue:
            node = queue.pop(0)
            if node not in visited:
                visited.append(node)
                queue.extend([neighbor[0] for neighbor in self.graph.get(node, [])])
        return visited

    def dfs(self, start, visited=None):
        if visited is None:
            visited = []
        visited.append(start)
        for neighbor, _ in self.graph.get(start, []):
            if neighbor not in visited:
                self.dfs(neighbor, visited)
        return visited


# Visualization Tool
class VisualizationTool:
    def _init_(self):
        self.tree = BinaryTree()
        self.graph = Graph()
        self.tree_root = None
        self.window = tk.Tk()
        self.window.title("Data Visualization Tool")
        self.create_ui()

    def create_ui(self):
        tk.Label(self.window, text="Tree Operations").grid(row=0, column=0)
        tk.Button(self.window, text="Insert Tree Node", command=self.insert_tree_node).grid(row=1, column=0)
        tk.Button(self.window, text="Show Tree Inorder", command=self.show_tree_inorder).grid(row=2, column=0)

        tk.Label(self.window, text="Graph Operations").grid(row=0, column=1)
        tk.Button(self.window, text="Add Graph Edge", command=self.add_graph_edge).grid(row=1, column=1)
        tk.Button(self.window, text="Show Graph BFS", command=self.show_graph_bfs).grid(row=2, column=1)

    def insert_tree_node(self):
        key = int(input("Enter node value: "))
        self.tree_root = self.tree.insert(self.tree_root, key)
        messagebox.showinfo("Tree Operation", f"Node {key} inserted!")

    def show_tree_inorder(self):
        traversal = self.tree.inorder(self.tree_root)
        messagebox.showinfo("Tree Traversal", f"In-order Traversal: {traversal}")

    def add_graph_edge(self):
        u = input("Enter starting node: ")
        v = input("Enter ending node: ")
        weight = int(input("Enter weight (default 1): ") or "1")
        self.graph.add_edge(u, v, weight)
        messagebox.showinfo("Graph Operation", f"Edge {u} -> {v} added!")

    def show_graph_bfs(self):
        start = input("Enter starting node for BFS: ")
        traversal = self.graph.bfs(start)
        messagebox.showinfo("Graph Traversal", f"BFS Traversal: {traversal}")

    def run(self):
        self.window.mainloop()


# Run the Visualization Tool
if _name_ == "_main_":
    tool = VisualizationTool()
    tool.run()
