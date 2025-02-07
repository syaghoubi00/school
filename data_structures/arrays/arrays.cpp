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

// Use a template to allow for any data type
template <typename T> void bonus_task_1(T arr[], int arrCount) {
  cout << "[";
  for (int i = 0; i < arrCount - 1; i++) {
    cout << sizeof(arr[i]) << ",";
  }
  // Special case for the last element to avoid trailing comma
  cout << sizeof(arr[arrCount - 1]) << "]" << endl;
}

// Redefine function to accept a pointer
template <typename T> void bonus_task_2(T *ptr, int size) {
  cout << "[";
  for (int i = 0; i < size - 1; i++) {
    cout << sizeof(ptr[i]) << ",";
  }
  cout << sizeof(ptr[size - 1]) << "]" << endl;
}

int main() {
  task_1();
  task_2();

  /* Bonus Task 1: Passing an array to a function and determining its size */

  int intArr[5] = {1, 2, 3, 4, 5};
  char charArr[5] = {'b', 'o', 'n', 'u', 's'};

  // Due to array decay, where the array turns into a pointer when passed into a
  // function, sizeof(arr) in the function will not give the correct size, so we
  // pass it in before the decay
  int intArrCount = sizeof(intArr) / sizeof(intArr[0]);

  cout << "Int Array: ";
  bonus_task_1(intArr, intArrCount);

  cout << "Char Array: ";
  bonus_task_1(charArr, (sizeof(charArr) / sizeof(charArr[0])));

  /* Bonus Task 2: Dynamic Arrays */

  // Create a dynamic array (stored on heap vs in stack)
  char *ptrArr = new char[5];

  for (int i = 0; i < 5; i++) {
    ptrArr[i] = 'a' + i; // Fill with a,b,c,d,e
  }

  cout << "Dynamic Array: ";
  // Must track dynamic array size manually
  bonus_task_2(ptrArr, 5);

  // Dynamic arrays aren't automatically cleaned up, so we have to delete them
  delete[] ptrArr;

  return 0;
}
