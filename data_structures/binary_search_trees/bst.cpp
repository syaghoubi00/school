#include <array>
#include <iostream>

template <typename T> struct BSTNode {
  T data;            // The value stored in this node, can be any type T
  BSTNode<T> *left;  // Pointer to the left child node
  BSTNode<T> *right; // Pointer to the right child node

  // Constructor
  BSTNode(T val) : data(val), left(nullptr), right(nullptr) {}
};

template <typename T> class BinarySearchTree {
private:
  BSTNode<T> *root; // Pointer to the root node of the tree

  // Private recursive helper method for insertion
  // Takes a node pointer and a value, returns the updated node pointer
  BSTNode<T> *insertHelper(BSTNode<T> *node, T val) {
    // Base case: if current node is null, create a new node with the value
    if (node == nullptr) {
      return new BSTNode<T>(val);
    }

    // If val is less than current node's data, insert in left subtree
    if (val < node->data) {
      node->left = insertHelper(node->left, val);
    }
    // If val is greater than current node's data, insert in right subtree
    else if (val > node->data) {
      node->right = insertHelper(node->right, val);
    }
    // If val equals current node's data, do nothing (no duplicates)

    // Return the (potentially modified) node pointer
    return node;
  }

  // Helper method for in-order traversal
  void printInOrderHelper(BSTNode<T> *node) {
    if (node != nullptr) {
      printInOrderHelper(node->left);  // Process left subtree
      std::cout << node->data << " ";  // Process current node
      printInOrderHelper(node->right); // Process right subtree
    }
  }

public:
  // Constructor
  BinarySearchTree() : root(nullptr) {}

  // Public insert method
  void insert(T val) {
    // Call the recursive helper method starting from the root
    root = insertHelper(root, val);
  }

  // Print the tree in-order (left, root, right)
  // This is useful for testing and verification
  void printInOrder() {
    std::cout << "In-order traversal: ";
    printInOrderHelper(root);
    std::cout << std::endl;
  }
};

int main() {
  // Initialize the array using the values provided in task 1
  std::array<int, 9> arr = {1, 5, 9, 2, 4, 10, 6, 3, 8};

  // Create an instance of the BinarySearchTree class with int type
  BinarySearchTree<int> bst;

  // For each value (val) in the array (arr), insert it into the binary search
  // tree
  for (int val : arr) {
    bst.insert(val);
  }

  // Print the tree in-order to verify it's working
  // This should output the elements in sorted order
  bst.printInOrder();

  return 0;
}
