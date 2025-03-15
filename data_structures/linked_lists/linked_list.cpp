/**
 * This file implements two types of linked list data structures:
 * 1. Singly Linked List - where each node points only to the next node
 * 2. Doubly Linked List - where each node points to both next and previous
 * nodes
 */

#include <iostream>

/* SINGLY LINKED LIST IMPLEMENTATION */

/**
 * Define the structure for a node in a singly linked list
 * Each node contains an integer value and a pointer to the next node
 */
struct ListNode {
  // The value stored in this node
  int data;
  // Pointer to the next node in the list (or nullptr if this is the last node)
  ListNode *next;
};

/**
 * Creates a new node for a singly linked list
 *
 * @param value The integer to store in the new node
 * @return Pointer to the newly created node
 */
ListNode *createListNode(int value) {
  // Allocate memory for a new ListNode
  ListNode *newNode = new ListNode;
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
 * @param headRef Pointer to the head pointer of the list (allows modification
 * of the head)
 * @param value The integer value to store in the new node
 */
void addToStartOfList(ListNode **headRef, int value) {
  // Create a new node with the given value
  ListNode *newNode = createListNode(value);

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
 * @param headRef Pointer to the head pointer of the list (allows modification
 * of the head if the list is empty)
 * @param value The integer value to store in the new node
 */
void addToEndOfList(ListNode **headRef, int value) {
  // Create a new node with the given value
  ListNode *newNode = createListNode(value);

  // If the list is empty, the new node becomes the head
  if (*headRef == nullptr) {
    *headRef = newNode;
  } else {
    // Otherwise, find the last node
    ListNode *current = *headRef;
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
 * @param headRef Pointer to the head pointer of the list (allows modification
 * of the head)
 */
void deleteAtStartOfList(ListNode **headRef) {
  // Check if the list is empty (head points to nullptr)
  if (*headRef == nullptr) {
    // If the list is empty, output a message and return without doing anything
    std::cout << "List is empty. Nothing to delete." << std::endl;
    return;
  }

  /* Store the current head node in a temporary pointer
   * This allows us to delete it after updating the head */
  ListNode *temp = *headRef;

  // Update the head to point to the second node
  // This removes the first node from the list structure
  *headRef = (*headRef)->next;

  // Save the value of the node being deleted for the confirmation message
  int deletedValue = temp->data;

  // Free the memory allocated for the old head node
  delete temp;

  // Output a confirmation message with the deleted value
  std::cout << "Deleted node with value " << deletedValue << " from the start"
            << std::endl;
}

/**
 * Deletes the last node from a singly linked list
 *
 * @param headRef Pointer to the head pointer of the list (allows modification
 * of the head in case the list has only one node)
 */
void deleteAtEndOfList(ListNode **headRef) {
  // Check if the list is empty
  if (*headRef == nullptr) {
    std::cout << "List is empty. Nothing to delete." << std::endl;
    return;
  }

  /* Special case: If there's only one node in the list
   * This is equivalent to deleting from the start */
  if ((*headRef)->next == nullptr) {
    // Store the value for the confirmation message
    int deletedValue = (*headRef)->data;
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
  ListNode *current = *headRef;
  ListNode *temp = current->next;

  // Navigate to the second-to-last node
  while (temp->next != nullptr) {
    current = current->next;
    temp = temp->next;
  }

  // Store the value of the node being deleted for the confirmation message
  int deletedValue = temp->data;

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
 *
 * @param head Pointer to the first node in the list
 */
void displayList(ListNode *head) {
  // Check if the list is empty
  if (head == nullptr) {
    std::cout << "List is empty" << std::endl;
    return;
  }

  // Print the start of the output message
  std::cout << "List elements: ";

  // Initialize current to the first node to start traversal
  ListNode *current = head;

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
void freeList(ListNode **headRef) {
  // current initially points to the first node
  ListNode *current = *headRef;
  // next will temporarily store the next node during deletion
  ListNode *next;

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
 * Define the structure for a node in a doubly linked list
 * Each node contains an integer value and pointers to both next and previous
 * nodes
 */
struct DListNode {
  int data;        // The value stored in this node
  DListNode *next; // Pointer to the next node in the list
  DListNode *prev; // Pointer to the previous node in the list
};

/**
 * Creates a new node for a doubly linked list
 *
 * @param value The integer to store in the new node
 * @return Pointer to the newly created node
 */
DListNode *createDListNode(int value) {
  // Allocate memory for a new DListNode
  DListNode *newNode = new DListNode;
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
void addToStartOfDList(DListNode **headRef, DListNode **tailRef, int value) {
  // Create a new node with the given value
  DListNode *newNode = createDListNode(value);

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
void addToEndOfDList(DListNode **headRef, DListNode **tailRef, int value) {
  // Create a new node with the given value
  DListNode *newNode = createDListNode(value);

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
void deleteAtStartOfDList(DListNode **headRef, DListNode **tailRef) {
  // Check if the list is empty
  if (*headRef == nullptr) {
    std::cout << "List is empty. Nothing to delete." << std::endl;
    return;
  }

  // Store the current head node in a temporary pointer
  DListNode *temp = *headRef;

  // Save the value of the node being deleted for the confirmation message
  int deletedValue = temp->data;

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
void deleteAtEndOfDList(DListNode **headRef, DListNode **tailRef) {
  // Check if the list is empty
  if (*tailRef == nullptr) {
    std::cout << "List is empty. Nothing to delete." << std::endl;
    return;
  }

  // Store the current tail node in a temporary pointer
  DListNode *temp = *tailRef;

  // Store the value of the node being deleted for the confirmation message
  int deletedValue = temp->data;

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
void displayForwardDList(DListNode *head) {
  // Check if the list is empty
  if (head == nullptr) {
    std::cout << "List is empty" << std::endl;
    return;
  }

  // Print the start of the output message
  std::cout << "List elements (forward): ";

  // Initialize current to the first node to start traversal
  DListNode *current = head;

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
void displayBackwardDList(DListNode *tail) {
  // Check if the list is empty
  if (tail == nullptr) {
    std::cout << "List is empty" << std::endl;
    return;
  }

  // Print the start of the output message
  std::cout << "List elements (backward): ";

  // Initialize current to the last node to start reverse traversal
  DListNode *current = tail;

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
void freeDList(DListNode **headRef, DListNode **tailRef) {
  // current initially points to the first node
  DListNode *current = *headRef;
  // next will temporarily store the next node during deletion
  DListNode *next;

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
  std::cout << "=== Linked List ===" << std::endl;
  // Initialize head pointer for singly linked list to nullptr (empty list)
  ListNode *singlyHead = nullptr;

  /**
   * Add three nodes to the beginning of the list
   * After these operations, the list will contain: 10 -> 20 -> 30
   */
  addToStartOfList(&singlyHead, 30); // List becomes: 30
  addToStartOfList(&singlyHead, 20); // List becomes: 20 -> 30
  addToStartOfList(&singlyHead, 10); // List becomes: 10 -> 20 -> 30

  // Display the current state of the list
  displayList(singlyHead); // Outputs: List elements: 10 -> 20 -> 30

  /**
   * Delete two nodes from the beginning of the list
   * This demonstrates removing elements from the singly linked list
   */
  deleteAtStartOfList(&singlyHead); // Removes 10, list becomes: 20 -> 30
  displayList(singlyHead);          // Outputs: List elements: 20 -> 30
  deleteAtStartOfList(&singlyHead); // Removes 20, list becomes: 30
  displayList(singlyHead);          // Outputs: List elements: 30

  // Free all memory used by the singly linked list
  freeList(&singlyHead);

  // Add a blank line between demonstrations
  std::cout << std::endl;

  /* Doubly Linked List operations */
  std::cout << "=== Doubly Linked List ===" << std::endl;

  // Initialize head and tail pointers for doubly linked list to nullptr
  // (emptylist)
  DListNode *doublyHead = nullptr;
  DListNode *doublyTail = nullptr;

  // Add three nodes to the beginning of the list
  // After these operations, the list will contain: 10 <-> 20 <-> 30
  addToStartOfDList(&doublyHead, &doublyTail, 30); // List becomes: 30
  addToStartOfDList(&doublyHead, &doublyTail, 20); // List becomes: 20 <-> 30
  addToStartOfDList(&doublyHead, &doublyTail,
                    10); // List becomes: 10 <-> 20 <-> 30

  // Display the current state of the list in both directions
  // This demonstrates the bidirectional nature of doubly linked lists
  displayForwardDList(
      doublyHead); // Outputs: List elements (forward): 10 <-> 20 <-> 30
  displayBackwardDList(
      doublyTail); // Outputs: List elements (backward): 30 <-> 20 <-> 10

  // Delete two nodes from the beginning of the list
  // This demonstrates removing elements from the doubly linked list
  deleteAtStartOfDList(&doublyHead,
                       &doublyTail); // Removes 10, list becomes: 20 <-> 30
  displayForwardDList(
      doublyHead); // Outputs: List elements (forward): 20 <-> 30
  deleteAtStartOfDList(&doublyHead,
                       &doublyTail); // Removes 20, list becomes: 30
  displayForwardDList(doublyHead);   // Outputs: List elements (forward): 30

  // Free all memory used by the doubly linked list
  freeDList(&doublyHead, &doublyTail);

  return 0;
}
