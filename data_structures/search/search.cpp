#include <iostream>
#include <vector>

/* Use const to prevent modification of the vector.
 * Passing a reference avoids copying the vector */
void linear_search(const std::vector<int> &vec, int target) {
  int steps = 0; // Counter to track number of comparisons

  // Check each element in the array
  for (int i = 0; i < vec.size(); i++) {
    steps++;

    if (vec[i] == target) {
      std::cout << "Linear Search: Found " << target << " in " << steps
                << " steps" << std::endl;
      return;
    }
  }

  // If target is not found, print the number of steps taken
  std::cout << "Linear Search: " << target << " not found after " << steps
            << " steps" << std::endl;
}

void binary_search(const std::vector<int> &vec, int target) {
  int steps = 0;              // Counter to track number of comparisons
  int left = 0;               // Left boundary of search interval
  int right = vec.size() - 1; // Right boundary of search interval

  // Continue searching while there are elements to check
  while (left <= right) {
    steps++;

    /* Calculate the middle point, avoiding potential integer overflow.
     * If adding (left + right) / 2, it may overflow for large values. Since
     * the right will always be greater than left, we can ensure we stay within
     * the range of valid integers. Additionally, integer division is always
     * truncated, which drops any remainder from the division operation; this
     * ensures a valid index. */
    int mid = left + (right - left) / 2;

    // Check if target is found at middle position
    if (vec[mid] == target) {
      std::cout << "Binary Search: Found " << target << " in " << steps
                << " steps" << std::endl;
      return;
    }

    // If target is greater, ignore left half
    if (vec[mid] < target)
      left = mid + 1;
    // If target is smaller, ignore right half
    else
      right = mid - 1;
  }

  // If target is not found, print the number of steps taken
  std::cout << "Binary Search: " << target << " not found after " << steps
            << " steps" << std::endl;
}

int main() {
  /* TASK 4:
   * Write a C++ code that implements the linear and binary search algorithms.
   * The algorithm should be able to calculate the number of steps against the
   * given search. */

  // Sorted array for binary search
  std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  // Value to search for
  int target = 8;

  linear_search(vec, target);
  binary_search(vec, target);

  return 0;
}
