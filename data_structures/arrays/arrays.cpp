#include <iostream>
using namespace std;

void task_1() {
  /* TASK 1:
   * Explain how to create an array of 100 elements. You can choose
   * any data type of your choice.
   */

  int arr[100] = {0}; // Create an array of 100 elements, all initialized to 0
}

void task_2() {
  /* TASK 2:
   * What will be the size of each element of an array.
   */

  int arr[100] = {0}; // Create an array of 100 elements, all initialized to 0

  // Get the element count by dividing the total size by the size of one element
  // (arrSizeTotal (400 bytes) / arrSizeElement (4 bytes) = 100 Elements)
  int arrElementCount = sizeof(arr) / sizeof(arr[0]);

  // Iterates over the elements of the array, getting the size of each element
  // printing the size (in bytes) of each element to stdout
  cout << "Byte Size of Each Element in Array: [";
  for (int i = 0; i < arrElementCount - 1; i++) {
    cout << sizeof(arr[i]) << ",";
  }
  // Special case for the last element to avoid trailing comma
  cout << sizeof(arrElementCount - 1) << "]" << endl;
}

void bonus_task() {
  /* Get the size of each element in an unknown sized array */
}

int main() {
  task_1();
  task_2();

  return 0;
}
