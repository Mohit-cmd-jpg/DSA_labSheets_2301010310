import tkinter as tk
from tkinter import messagebox


class Product:
    def _init_(self, product_id, name, category, price, rating):
        self.id = product_id
        self.name = name
        self.category = category
        self.price = price
        self.rating = rating

    def _repr_(self):
        return f"{self.name} (ID: {self.id}, Price: {self.price}, Rating: {self.rating})"


class ECommerceSystem:
    def _init_(self):
        self.products = []
        self.window = tk.Tk()
        self.window.title("E-Commerce Search and Sort System")
        self.create_ui()

    def create_ui(self):
        tk.Label(self.window, text="E-Commerce System").grid(row=0, column=0, columnspan=2)

        tk.Button(self.window, text="Add Product", command=self.add_product).grid(row=1, column=0)
        tk.Button(self.window, text="Sort by Price (QuickSort)", command=self.sort_by_price).grid(row=2, column=0)
        tk.Button(self.window, text="Search by ID (Binary Search)", command=self.search_by_id).grid(row=3, column=0)
        tk.Button(self.window, text="Sort by Rating (Merge Sort)", command=self.sort_by_rating).grid(row=4, column=0)
        tk.Button(self.window, text="Show All Products", command=self.show_products).grid(row=5, column=0)

    def add_product(self):
        try:
            product_id = int(input("Enter Product ID: "))
            name = input("Enter Product Name: ")
            category = input("Enter Product Category: ")
            price = float(input("Enter Product Price: "))
            rating = float(input("Enter Product Rating: "))
            product = Product(product_id, name, category, price, rating)
            self.products.append(product)
            messagebox.showinfo("Product Added", f"Product '{name}' added successfully!")
        except ValueError:
            messagebox.showerror("Input Error", "Invalid input. Please enter valid details.")

    def quicksort(self, array, key=lambda x: x):
        if len(array) <= 1:
            return array
        pivot = array[len(array) // 2]
        left = [x for x in array if key(x) < key(pivot)]
        middle = [x for x in array if key(x) == key(pivot)]
        right = [x for x in array if key(x) > key(pivot)]
        return self.quicksort(left, key) + middle + self.quicksort(right, key)

    def merge_sort(self, array, key=lambda x: x):
        if len(array) > 1:
            mid = len(array) // 2
            left_half = self.merge_sort(array[:mid], key)
            right_half = self.merge_sort(array[mid:], key)

            merged = []
            while left_half and right_half:
                if key(left_half[0]) < key(right_half[0]):
                    merged.append(left_half.pop(0))
                else:
                    merged.append(right_half.pop(0))
            return merged + left_half + right_half
        return array

    def binary_search(self, array, target_id):
        low, high = 0, len(array) - 1
        while low <= high:
            mid = (low + high) // 2
            if array[mid].id == target_id:
                return array[mid]
            elif array[mid].id < target_id:
                low = mid + 1
            else:
                high = mid - 1
        return None

    def sort_by_price(self):
        self.products = self.quicksort(self.products, key=lambda x: x.price)
        messagebox.showinfo("Sorted", "Products sorted by price!")

    def sort_by_rating(self):
        self.products = self.merge_sort(self.products, key=lambda x: x.rating)
        messagebox.showinfo("Sorted", "Products sorted by rating!")

    def search_by_id(self):
        if not self.products:
            messagebox.showerror("Error", "No products available to search.")
            return

        self.products = self.quicksort(self.products, key=lambda x: x.id)
        try:
            target_id = int(input("Enter Product ID to search: "))
            result = self.binary_search(self.products, target_id)
            if result:
                messagebox.showinfo("Search Result", f"Product Found: {result}")
            else:
                messagebox.showinfo("Search Result", "Product not found.")
        except ValueError:
            messagebox.showerror("Input Error", "Please enter a valid Product ID.")

    def show_products(self):
        if self.products:
            product_list = "\n".join(str(product) for product in self.products)
            messagebox.showinfo("Product List", product_list)
        else:
            messagebox.showinfo("Product List", "No products available.")

    def run(self):
        self.window.mainloop()


if _name_ == "_main_":
    ecommerce_system = ECommerceSystem()
    ecommerce_system.run()
