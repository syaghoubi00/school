/**
 * This file implements two types of linked list data structures:
 * 1. Singly Linked List - where each node points only to the next node
 * 2. Doubly Linked List - where each node points to both next and previous
 * nodes
 */

#include <iostream>
#include <string>

/* SINGLY LINKED LIST IMPLEMENTATION */

/**
 * Template definition for a node in a singly linked list
 * Each node contains a value of type T and a pointer to the next node
 */
template <typename T> struct ListNode {
  T data;            // The value stored in this node, can be any type T
  ListNode<T> *next; // Pointer to the next node in the list
};

/**
 * Creates a new node for a singly linked list
 *
 * @param value The value of type T to store in the new node
 * @return Pointer to the newly created node
 */
template <typename T> ListNode<T> *createListNode(T value) {
  // Allocate memory for a new ListNode
  ListNode<T> *newNode = new ListNode<T>;
  // Initialize the node's data field with the provided value
  newNode->data = value;
  // Initialize the next pointer to nullptr (indicating no next node yet)
  newNode->next = nullptr;
  // Return a pointer to the newly created node
  return newNode;
}

/**
 * Adds a new node at the beginning of a singly linked list
 *
 * @param headRef Pointer to the head pointer of the list
 * @param value The value of type T to store in the new node
 */
template <typename T> void addToStartOfList(ListNode<T> **headRef, T value) {
  // Create a new node with the given value
  ListNode<T> *newNode = createListNode(value);

  /* Make the new node point to the current head of the list
   * This connects the new node to the existing list */
  newNode->next = *headRef;

  // Update the head to point to the new node
  // This makes the new node the first element in the list
  *headRef = newNode;

  // Output a confirmation message
  std::cout << "Added node with value " << value << " at the start"
            << std::endl;
}

/**
 * Adds a new node at the end of a singly linked list
 *
 * @param headRef Pointer to the head pointer of the list
 * @param value The value of type T to store in the new node
 */
template <typename T> void addToEndOfList(ListNode<T> **headRef, T value) {
  // Create a new node with the given value
  ListNode<T> *newNode = createListNode(value);

  // If the list is empty, the new node becomes the head
  if (*headRef == nullptr) {
    *headRef = newNode;
  } else {
    // Otherwise, find the last node
    ListNode<T> *current = *headRef;
    while (current->next != nullptr) {
      current = current->next;
    }

    // Connect the last node to the new node
    current->next = newNode;
  }

  // Output a confirmation message
  std::cout << "Added node with value " << value << " at the end" << std::endl;
}

/**
 * Deletes the first node from a singly linked list
 *
 * @param headRef Pointer to the head pointer of the list
 */
template <typename T> void deleteAtStartOfList(ListNode<T> **headRef) {
  // Check if the list is empty (head points to nullptr)
  if (*headRef == nullptr) {
    // If the list is empty, output a message and return without doing anything
    std::cout << "List is empty. Nothing to delete." << std::endl;
    return;
  }

  /* Store the current head node in a temporary pointer
   * This allows us to delete it after updating the head */
  ListNode<T> *temp = *headRef;

  // Update the head to point to the second node
  // This removes the first node from the list structure
  *headRef = (*headRef)->next;

  // Save the value of the node being deleted for the confirmation message
  auto deletedValue = temp->data;

  // Free the memory allocated for the old head node
  delete temp;

  // Output a confirmation message with the deleted value
  std::cout << "Deleted node with value " << deletedValue << " from the start"
            << std::endl;
}

/**
 * Deletes the last node from a singly linked list
 *
 * @param headRef Pointer to the head pointer of the list
 */
template <typename T> void deleteAtEndOfList(ListNode<T> **headRef) {
  // Check if the list is empty
  if (*headRef == nullptr) {
    std::cout << "List is empty. Nothing to delete." << std::endl;
    return;
  }

  /* Special case: If there's only one node in the list
   * This is equivalent to deleting from the start */
  if ((*headRef)->next == nullptr) {
    // Store the value for the confirmation message
    auto deletedValue = (*headRef)->data;
    // Delete the only node
    delete *headRef;
    // Set head to nullptr (empty list)
    *headRef = nullptr;
    // Output confirmation message
    std::cout << "Deleted node with value " << deletedValue << " from the end"
              << std::endl;
    return;
  }

  /* For a list with multiple nodes, we need to find the second-to-last node
   * We'll use two pointers: current will eventually point to the second-to-last
   * node, and temp will point to the last node */
  ListNode<T> *current = *headRef;
  ListNode<T> *temp = current->next;

  // Navigate to the second-to-last node
  while (temp->next != nullptr) {
    current = current->next;
    temp = temp->next;
  }

  // Store the value of the node being deleted for the confirmation message
  auto deletedValue = temp->data;

  // Delete the last node
  delete temp;

  // Update the second-to-last node's next pointer to nullptr
  // This makes it the new last node
  current->next = nullptr;

  // Output a confirmation message with the deleted value
  std::cout << "Deleted node with value " << deletedValue << " from the end"
            << std::endl;
}

/**
 * Displays all elements in a singly linked list
 * Requires the type T to have operator<< defined
 *
 * @param head Pointer to the first node in the list
 */
template <typename T> void displayList(ListNode<T> *head) {
  // Check if the list is empty
  if (head == nullptr) {
    std::cout << "List is empty" << std::endl;
    return;
  }

  // Print the start of the output message
  std::cout << "List elements: ";

  // Initialize current to the first node to start traversal
  ListNode<T> *current = head;

  /* Traverse the list from head to tail
   * Print each element and follow the next pointers */
  while (current != nullptr) {
    // Print the value in the current node
    std::cout << current->data;

    // Move to the next node
    current = current->next;

    // If there's another node after this one, print an arrow
    // This creates a visual representation of the links between nodes
    if (current != nullptr) {
      std::cout << " -> ";
    }
  }

  // End the output with a newline
  std::cout << std::endl;
}

/**
 * Frees all memory used by a singly linked list
 *
 * @param headRef Pointer to the head pointer of the list (allows setting head
 * to nullptr)
 */
template <typename T> void freeList(ListNode<T> **headRef) {
  // current initially points to the first node
  ListNode<T> *current = *headRef;
  // next will temporarily store the next node during deletion
  ListNode<T> *next;

  /* Traverse the list and delete each node
   * We need to save the next pointer before deleting the current node */
  while (current != nullptr) {
    // Store the pointer to the next node before deleting the current one
    next = current->next;
    // Free the memory allocated for the current node
    delete current;
    // Move to the next node
    current = next;
  }

  // Set the head pointer to nullptr to indicate an empty list
  *headRef = nullptr;
}

/*  DOUBLY LINKED LIST IMPLEMENTATION */

/**
 * Template definition for a node in a doubly linked list
 * Each node contains a value of type T and pointers to both next and previous
 * nodes
 */
template <typename T> struct DListNode {
  T data;             // The value stored in this node, can be any type T
  DListNode<T> *next; // Pointer to the next node in the list
  DListNode<T> *prev; // Pointer to the previous node in the list
};

/**
 * Creates a new node for a doubly linked list
 *
 * @param value The value of type T to store in the new node
 * @return Pointer to the newly created node
 */
template <typename T> DListNode<T> *createDListNode(T value) {
  // Allocate memory for a new DListNode
  DListNode<T> *newNode = new DListNode<T>;
  // Initialize the node's data field with the provided value
  newNode->data = value;
  // Initialize the next pointer to nullptr (indicating no next node yet)
  newNode->next = nullptr;
  // Initialize the prev pointer to nullptr (indicating no previous node yet)
  newNode->prev = nullptr;
  // Return a pointer to the newly created node
  return newNode;
}

/**
 * Adds a new node at the beginning of a doubly linked list
 *
 * @param headRef Pointer to the head pointer of the list
 * @param tailRef Pointer to the tail pointer of the list
 * @param value The integer value to store in the new node
 */
template <typename T>
void addToStartOfDList(DListNode<T> **headRef, DListNode<T> **tailRef,
                       T value) {
  // Create a new node with the given value
  DListNode<T> *newNode = createDListNode(value);

  /* If the list is empty, the new node becomes both head and tail
   * This handles the special case of the first element */
  if (*headRef == nullptr) {
    *headRef = newNode;
    *tailRef = newNode;
  } else {
    // Make the new node point to the current head
    newNode->next = *headRef;

    /* Make the current head's prev pointer point to the new node
     * This establishes the double linkage */
    (*headRef)->prev = newNode;

    // Update the head to point to the new node
    *headRef = newNode;
  }

  // Output a confirmation message
  std::cout << "Added node with value " << value << " at the start"
            << std::endl;
}

/**
 * Adds a new node at the end of a doubly linked list
 *
 * @param headRef Pointer to the head pointer of the list
 * @param tailRef Pointer to the tail pointer of the list
 * @param value The integer value to store in the new node
 */
template <typename T>
void addToEndOfDList(DListNode<T> **headRef, DListNode<T> **tailRef, T value) {
  // Create a new node with the given value
  DListNode<T> *newNode = createDListNode(value);

  /* If the list is empty, the new node becomes both head and tail
   * This handles the special case of the first element */
  if (*headRef == nullptr) {
    *headRef = newNode;
    *tailRef = newNode;
  } else {
    // Make the new node's prev pointer point to the current tail
    newNode->prev = *tailRef;

    // Make the current tail's next pointer point to the new node
    (*tailRef)->next = newNode;

    // Update the tail to point to the new node
    *tailRef = newNode;
  }

  // Output a confirmation message
  std::cout << "Added node with value " << value << " at the end" << std::endl;
}

/**
 * Deletes the first node from a doubly linked list
 *
 * @param headRef Pointer to the head pointer of the list
 * @param tailRef Pointer to the tail pointer of the list
 */
template <typename T>
void deleteAtStartOfDList(DListNode<T> **headRef, DListNode<T> **tailRef) {
  // Check if the list is empty
  if (*headRef == nullptr) {
    std::cout << "List is empty. Nothing to delete." << std::endl;
    return;
  }

  // Store the current head node in a temporary pointer
  DListNode<T> *temp = *headRef;

  // Save the value of the node being deleted for the confirmation message
  auto deletedValue = temp->data;

  /* If there's only one node in the list
   * We need to handle this special case by setting both head and tail to
   * nullptr */
  if (*headRef == *tailRef) {
    // Set both head and tail to nullptr, making the list empty
    *headRef = nullptr;
    *tailRef = nullptr;
  } else {
    // Update head to point to the second node
    *headRef = (*headRef)->next;

    /* Make the new head's prev pointer point to nullptr
     * This maintains the integrity of the doubly linked list */
    (*headRef)->prev = nullptr;
  }

  // Free the memory allocated for the old head node
  delete temp;

  // Output a confirmation message
  std::cout << "Deleted node with value " << deletedValue << " from the start"
            << std::endl;
}

/**
 * Deletes the last node from a doubly linked list
 *
 * @param headRef Pointer to the head pointer of the list
 * @param tailRef Pointer to the tail pointer of the list
 */
template <typename T>
void deleteAtEndOfDList(DListNode<T> **headRef, DListNode<T> **tailRef) {
  // Check if the list is empty
  if (*tailRef == nullptr) {
    std::cout << "List is empty. Nothing to delete." << std::endl;
    return;
  }

  // Store the current tail node in a temporary pointer
  DListNode<T> *temp = *tailRef;

  // Store the value of the node being deleted for the confirmation message
  auto deletedValue = temp->data;

  /* If there's only one node in the list
   * We need to handle this special case by setting both head and tail to
   * nullptr */
  if (*headRef == *tailRef) {
    // Set both head and tail to nullptr, making the list empty
    *headRef = nullptr;
    *tailRef = nullptr;
  } else {
    // Update tail to point to the second-to-last node
    *tailRef = (*tailRef)->prev;

    /* Make the new tail's next pointer point to nullptr
     * This maintains the integrity of the doubly linked list */
    (*tailRef)->next = nullptr;
  }

  // Free the memory allocated for the old tail node
  delete temp;

  // Output a confirmation message with the deleted value
  std::cout << "Deleted node with value " << deletedValue << " from the end"
            << std::endl;
}

/**
 * Displays all elements in a doubly linked list (from head to tail)
 *
 * @param head Pointer to the first node in the list
 */
template <typename T> void displayForwardDList(DListNode<T> *head) {
  // Check if the list is empty
  if (head == nullptr) {
    std::cout << "List is empty" << std::endl;
    return;
  }

  // Print the start of the output message
  std::cout << "List elements (forward): ";

  // Initialize current to the first node to start traversal
  DListNode<T> *current = head;

  /* Traverse the list from head to tail
   * Print each element as we go */
  while (current != nullptr) {
    // Print the value in the current node
    std::cout << current->data;
    // Move to the next node
    current = current->next;

    // If there's another node after this one, print a bidirectional arrow
    if (current != nullptr) {
      std::cout << " <-> ";
    }
  }

  // End the output with a newline
  std::cout << std::endl;
}

/**
 * Displays all elements in a doubly linked list (from tail to head)
 *
 * @param tail Pointer to the last node in the list
 */
template <typename T> void displayBackwardDList(DListNode<T> *tail) {
  // Check if the list is empty
  if (tail == nullptr) {
    std::cout << "List is empty" << std::endl;
    return;
  }

  // Print the start of the output message
  std::cout << "List elements (backward): ";

  // Initialize current to the last node to start reverse traversal
  DListNode<T> *current = tail;

  /* Traverse the list from tail to head
   * Following the prev pointers backward through the list */
  while (current != nullptr) {
    // Print the value in the current node
    std::cout << current->data;
    // Move to the previous node
    current = current->prev;

    // If there's another node before this one, print a bidirectional arrow
    if (current != nullptr) {
      std::cout << " <-> ";
    }
  }

  // End the output with a newline
  std::cout << std::endl;
}

/**
 * Frees all memory used by a doubly linked list
 *
 * @param headRef Pointer to the head pointer of the list
 * @param tailRef Pointer to the tail pointer of the list
 */
template <typename T>
void freeDList(DListNode<T> **headRef, DListNode<T> **tailRef) {
  // current initially points to the first node
  DListNode<T> *current = *headRef;
  // next will temporarily store the next node during deletion
  DListNode<T> *next;

  /* Traverse the list and delete each node
   * Similar to the singly linked list cleanup */
  while (current != nullptr) {
    // Store the pointer to the next node before deleting the current one
    next = current->next;
    // Free the memory allocated for the current node
    delete current;
    // Move to the next node
    current = next;
  }

  // Set both head and tail pointers to nullptr to indicate an empty list
  *headRef = nullptr;
  *tailRef = nullptr;
}

int main() {
  /* Singly Linked List operations */
  std::cout << "=== Integer Linked List ===" << std::endl;
  // Initialize head pointer for singly linked list to nullptr (empty list)
  ListNode<int> *intHead = nullptr;

  /**
   * Add three nodes to the beginning of the list
   * After these operations, the list will contain: 10 -> 20 -> 30
   */
  addToStartOfList(&intHead, 30); // List becomes: 30
  addToStartOfList(&intHead, 20); // List becomes: 20 -> 30
  addToStartOfList(&intHead, 10); // List becomes: 10 -> 20 -> 30

  // Display the current state of the list
  displayList(intHead); // Outputs: List elements: 10 -> 20 -> 30

  // Delete node from the beginning of the list
  deleteAtStartOfList(&intHead); // Removes 10, list becomes: 20 -> 30
  displayList(intHead);          // Outputs: List elements: 20 -> 30

  // Delete node from the end of the list
  deleteAtEndOfList(&intHead); // Removes 30, list becomes: 20
  displayList(intHead);        // Outputs: List elements: 20

  // Free all memory used by the singly linked list
  freeList(&intHead);

  // Add a blank line between demonstrations
  std::cout << std::endl;

  // Demonstrate Singly Linked List with strings
  std::cout << "=== String Linked List ===" << std::endl;
  ListNode<std::string> *stringHead = nullptr;

  addToStartOfList(&stringHead, std::string("world"));
  addToStartOfList(&stringHead, std::string("hello"));
  displayList(stringHead);

  std::cout << std::endl;

  /* Doubly Linked List operations */
  std::cout << "=== Double Doubly Linked List ===" << std::endl;

  // Initialize head and tail pointers for doubly linked list to nullptr
  // (emptylist)
  DListNode<double> *doubleDHead = nullptr;
  DListNode<double> *doubleDTail = nullptr;

  // Add three nodes to the beginning of the list
  // After these operations, the list will contain: 1.23 <-> 2.34 <-> 3.45
  addToStartOfDList(&doubleDHead, &doubleDTail, 1.23); // List becomes: 1.23
  addToStartOfDList(&doubleDHead, &doubleDTail,
                    2.34); // List becomes: 1.23 <-> 2.34
  addToStartOfDList(&doubleDHead, &doubleDTail,
                    3.45); // List becomes: 1.23 <-> 2.34 <-> 3.45

  // Display the current state of the list in both directions
  // This demonstrates the bidirectional nature of doubly linked lists
  displayForwardDList(
      doubleDHead); // Outputs: List elements (forward): 1.23 <-> 2.34 <-> 3.45
  displayBackwardDList(
      doubleDTail); // Outputs: List elements (backward): 3.45 <-> 2.34 <-> 1.23

  // Delete nodes from the beginning and end of the list
  // This demonstrates removing elements from the doubly linked list
  deleteAtStartOfDList(
      &doubleDHead,
      &doubleDTail); // Removes 1.23, list becomes: 2.34 <-> 3.45
  displayForwardDList(
      doubleDHead); // Outputs: List elements (forward): 2.34 <-> 3.45
  deleteAtEndOfDList(&doubleDHead,
                     &doubleDTail); // Removes 3.45, list becomes: 2.34
  displayForwardDList(doubleDHead); // Outputs: List elements (forward): 2.34

  // Free all memory used by the doubly linked list
  freeDList(&doubleDHead, &doubleDTail);

  return 0;
}
