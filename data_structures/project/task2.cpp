#include <iostream>
#include <vector>

int findMissingNumber(const std::vector<int> &nums) {
  int n = nums.size(); // The array size is N (missing one number)
  int expectedSum =
      n * (n + 1) / 2; // Use the formula for the sum of N natural
                       // numbers in the arithmetic series since the input is
                       // ordered 0...N and missing one number
  int actualSum = 0;

  // Calculate the sum of elements in the array - O(n) operation
  for (int num : nums) {
    actualSum += num;
  }

  return expectedSum - actualSum; // The difference is the missing number
}

// Helper function to find and print the missing number
void testMissingNumber(const std::vector<int> &nums) {
  std::cout << "Missing number: " << findMissingNumber(nums) << std::endl;
}

int main() {
  std::vector<int> nums1 = {2, 3, 0, 6, 1, 5};
  std::vector<int> nums2 = {8, 2, 3, 9, 4, 7, 5, 0, 6};

  testMissingNumber(nums1);
  testMissingNumber(nums2);

  return 0;
}
