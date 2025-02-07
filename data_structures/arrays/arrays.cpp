#include <array>
#include <iostream>

using std::cout;
using std::endl;

void task_1() {
  /* TASK 1:
   * Explain how to create an array of 100 elements. You can choose
   * any data type of your choice.
   */

  // Create an array of 100 elements, all initialized to 0

  int cArr[100] = {0};           // C style array
  std::array<int, 100> cppArr{}; // C++ style array
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
  cout << sizeof(arr[arrElementCount - 1]) << "]" << endl;
}

// Use a template to allow for any data type
// NOTE: The array notation `T arr[]` is equivalent to `T* arr`
template <typename T> void bonus_task(T arr[], int arrCount) {
  cout << "[";
  for (int i = 0; i < arrCount - 1; i++) {
    cout << sizeof(arr[i]) << ",";
  }
  // Special case for the last element to avoid trailing comma
  cout << sizeof(arr[arrCount - 1]) << "]" << endl;
}

int main() {
  task_1();
  task_2();

  /* Bonus Task 1: Passing an array to a function and determining its size */

  // C++ Style
  std::array<int, 5> intArr{1, 2, 3, 4, 5};
  cout << "Int Array: ";
  bonus_task(intArr.data(), intArr.size());

  // C Style
  char charArr[5] = {'b', 'o', 'n', 'u', 's'};
  cout << "Char Array: ";
  // Due to array decay, where the array turns into a pointer when passed into a
  // function, sizeof(arr) in the function will not give the correct size, so we
  // pass it in before the decay
  bonus_task(charArr, sizeof(charArr) / sizeof(charArr[0]));

  /* Bonus Task 2: Dynamic Arrays */

  // Create a dynamic array (stored on heap vs in stack)
  char *ptrArr = new char[5];

  for (int i = 0; i < 5; i++) {
    ptrArr[i] = 'a' + i; // Fill with a,b,c,d,e
  }

  cout << "Dynamic Array: ";
  // Must track dynamic array size manually
  bonus_task(ptrArr, 5);

  // Dynamic arrays aren't automatically cleaned up, so we have to delete them
  delete[] ptrArr;

  return 0;
}
