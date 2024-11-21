#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>

using namespace std;

// Product Class
class Product {
public:
    int id;
    string name;
    string category;
    double price;
    double rating;

    Product(int product_id, string name, string category, double price, double rating) 
        : id(product_id), name(name), category(category), price(price), rating(rating) {}

    string toString() const {
        return name + " (ID: " + to_string(id) + ", Price: " + to_string(price) + ", Rating: " + to_string(rating) + ")";
    }
};

// ECommerceSystem Class
class ECommerceSystem {
private:
    vector<Product> products;

public:
    void run() {
        while (true) {
            cout << "\nMenu:\n"
                 << "1. Add Product\n"
                 << "2. Sort by Price (QuickSort)\n"
                 << "3. Search by ID (Binary Search)\n"
                 << "4. Sort by Rating (Merge Sort)\n"
                 << "5. Show All Products\n"
                 << "6. Exit\n"
                 << "Enter your choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    addProduct();
                    break;
                case 2:
                    sortByPrice();
                    break;
                case 3:
                    searchById();
                    break;
                case 4:
                    sortByRating();
                    break;
                case 5:
                    showProducts();
                    break;
                case 6:
                    return;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
    }

private:
    void addProduct() {
        try {
            int product_id;
            string name, category;
            double price, rating;

            cout << "Enter Product ID: ";
            cin >> product_id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            cout << "Enter Product Name: ";
            getline(cin, name);
            cout << "Enter Product Category: ";
            getline(cin, category);
            cout << "Enter Product Price: ";
            cin >> price;
            cout << "Enter Product Rating: ";
            cin >> rating;

            products.emplace_back(product_id, name, category, price, rating);
            cout << "Product '" << name << "' added successfully!\n";
        } catch (const exception& e) {
            cout << "Invalid input. Please enter valid details.\n";
        }
    }

    vector<Product> quicksort(const vector<Product>& array, function<double(const Product&)> key) {
        if (array.size() <= 1) return array;

        auto pivot = array[array.size() / 2];
        vector<Product> left, middle, right;

        for (const auto& product : array) {
            if (key(product) < key(pivot))
                left.push_back(product);
            else if (key(product) == key(pivot))
                middle.push_back(product);
            else
                right.push_back(product);
        }

        auto sorted_left = quicksort(left, key);
        auto sorted_right = quicksort(right, key);

        sorted_left.insert(sorted_left.end(), middle.begin(), middle.end());
        sorted_left.insert(sorted_left.end(), sorted_right.begin(), sorted_right.end());
        return sorted_left;
    }

    vector<Product> mergeSort(vector<Product> array, function<double(const Product&)> key) {
        if (array.size() <= 1) return array;

        size_t mid = array.size() / 2;
        auto left_half = mergeSort(vector<Product>(array.begin(), array.begin() + mid), key);
        auto right_half = mergeSort(vector<Product>(array.begin() + mid, array.end()), key);

        vector<Product> merged;
        size_t i = 0, j = 0;
        while (i < left_half.size() && j < right_half.size()) {
            if (key(left_half[i]) < key(right_half[j])) {
                merged.push_back(left_half[i]);
                i++;
            } else {
                merged.push_back(right_half[j]);
                j++;
            }
        }

        while (i < left_half.size()) {
            merged.push_back(left_half[i]);
            i++;
        }

        while (j < right_half.size()) {
            merged.push_back(right_half[j]);
            j++;
        }

        return merged;
    }

    void sortByPrice() {
        products = quicksort(products, [](const Product& p) { return p.price; });
        cout << "Products sorted by price!\n";
    }

    void sortByRating() {
        products = mergeSort(products, [](const Product& p) { return p.rating; });
        cout << "Products sorted by rating!\n";
    }

    void searchById() {
        if (products.empty()) {
            cout << "No products available to search.\n";
            return;
        }

        // Sort by ID for binary search
        products = quicksort(products, [](const Product& p) { return p.id; });

        cout << "Enter Product ID to search: ";
        int target_id;
        cin >> target_id;

        int low = 0, high = products.size() - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (products[mid].id == target_id) {
                cout << "Product Found: " << products[mid].toString() << "\n";
                return;
            } else if (products[mid].id < target_id) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        cout << "Product not found.\n";
    }

    void showProducts() {
        if (products.empty()) {
            cout << "No products available.\n";
        } else {
            cout << "Product List:\n";
            for (const auto& product : products) {
                cout << product.toString() << "\n";
            }
        }
    }
};

// Main Function
int main() {
    ECommerceSystem system;
    system.run();
    return 0;
}
