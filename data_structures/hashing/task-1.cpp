#include <array>
#include <iostream>
#include <unordered_map>

template <typename T> void printMap(T &map) {
  std::cout << "Hash Table:" << std::endl;
  std::cout << "{" << std::endl;
  for (const auto &pair : map) {
    std::cout << pair.first << ":" << pair.second << "," << std::endl;
  }
  std::cout << "}" << std::endl;
}

void task_1(const int array[], const int arraySize, const int target) {
  /* Task 1:
   * Assume you have a simple single-dimensional array:
   * `array = [200, 400, 100, 50, 350]`
   * Linear search will take O(n). Write a code in C++/Python to improve the
   * search operation efficiency from O(n) to O(1)
   */

  // Build the lookup hash table - this is a one-time O(n) operation
  // After this, we can perform searches in O(1) time

  std::cout << "Original Array: " << "[ ";
  for (int i = 0; i < arraySize; i++) {
    std::cout << array[i] << " ";
  }
  std::cout << "]" << std::endl;

  std::unordered_map<int, int> hashTable;
  std::cout << "Building Hash Table..." << std::endl;
  for (int i = 0; i < arraySize; i++) {
    // For each element in the array, store its value as key and index as value
    // NOTE: If duplicates exist, this will keep the last occurrence's index
    hashTable[array[i]] = i;
  }

  // Print the hash table contents for demonstration.
  // Would be O(n). Not part of the O(1) search operation.
  printMap(hashTable);

  // Search method with O(1) time complexity
  auto iter = hashTable.find(target);
  if (iter != hashTable.end()) {
    std::cout << target << " is at index " << iter->second << " in the array"
              << std::endl;
  } else {
    std::cout << target << " not found" << std::endl;
  }
}

void bonus_task() {
  std::unordered_map<std::string, std::string> emailDirectory;

  // Insert items into the hash table - all O(1) operations
  emailDirectory["Alice"] = "alice@example.com";
  emailDirectory["Bob"] = "bob@example.com";
  emailDirectory["Charlie"] = "charlie@example.com";

  // Lookup items in the hash table - all O(1) operations
  std::string lookupName = "Bob";

  std::cout << "Email Directory Hash Table Lookup: " << std::endl;

  /*
   * `.find(key)` in STL containers like `std::unordered_map` returns an
   * iterator:
   *   - An iterator is a pointer-like object that refers to an element in a
   *     container
   *   - For maps/unordered_maps, this iterator points to a
   *   `std::pair<const KeyType, ValueType>`
   *   - If the key is found, it returns an iterator pointing to the key-value
   *     pair
   *   - If the key is NOT found, it returns the same iterator as `.end()`
   *
   * `.end()` returns a special iterator:
   *   - It points to the position after the last element in the container
   *   - It does not point to an actual element (dereferencing it causes
   *     undefined behavior)
   *   - It's used as a sentinel value to indicate "not found" or "past the end"
   *   - It's NOT a null pointer
   */

  // Bool method to check if an element exists in the hash table
  // 0 is false, 1 is true
  bool keyExistance = (emailDirectory.find(lookupName) != emailDirectory.end());
  if (keyExistance) {
    std::cout << lookupName << " exists in the directory." << std::endl;
  }

  // Check if an element exists in the hash table, using key check in if
  // statement instead of bool method
  if (emailDirectory.find(lookupName) != emailDirectory.end()) {
    std::cout << lookupName
              << "'s email address is: " << emailDirectory[lookupName]
              << std::endl;
  } else {
    std::cout << "No email address found for " << lookupName << "."
              << std::endl;
  }

  std::cout << "---" << std::endl;
  std::cout << "Using iterator to access the kv store:" << std::endl;
  auto iter = emailDirectory.find(lookupName);
  if (iter != emailDirectory.end()) {
    // Use it->first (the key) and it->second (the value)
    std::cout << iter->first << " has email: " << iter->second << std::endl;

    // You can also modify the value (but not the key) in O(1) time.
    // Changing the domain of the email address, retaining the user
    std::string newDomain = "example.net";

    // Doesn't preserve case because it uses the name key. Would need to
    // be transformed to lowercase.
    iter->second = iter->first + "@" + newDomain;

    std::cout << "Updated " << iter->first << "'s email: " << iter->second
              << std::endl;
  }
}

int main() {
  // Using the original array
  std::array<int, 5> arr = {200, 400, 100, 50, 350};
  int target = 100;
  task_1(arr.data(), arr.size(), target);
  std::cout << "---" << std::endl;

  bonus_task();
  std::cout << "---" << std::endl;

  return 0;
}
