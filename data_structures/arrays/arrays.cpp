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

  // Get the total size of the array in bytes
  int arrSize = sizeof(arr);

  // Get the element count by dividing the total size by the size of one element
  // (arrSize (400 bytes) / sizeOfElement (4 bytes) = 100 Elements)
  int arrElementCount = arrSize / sizeof(arr[0]);

  // Create an array of the same size as the original array
  int arrElementSizes[arrElementCount];
  // Iterates over the elements of the array, getting the size of each element
  for (int i = 0; i < arrElementCount; i++) {
    arrElementSizes[i] = sizeof(arr[i]);
  }

  // Interates over the elements of the array containing the sizes of each
  // element, printing the size (in bytes) of eeach element to stdout
  cout << "Size of Each Element in Array: [";
  for (int i = 0; i < arrElementCount - 1; i++) {
    cout << arrElementSizes[i] << ",";
  }
  // Speecial case for the last element to avoid trailing comma
  cout << arrElementSizes[arrElementCount - 1] << "]" << endl;
}

void bonus_task() {
  /* Get the size of each element in an unknown sized array */
}

int main() {
  task_1();
  task_2();

  return 0;
}
