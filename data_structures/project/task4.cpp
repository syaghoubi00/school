#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int highestProductOfTwo(const std::vector<int> &nums) {
  if (nums.size() < 2) {
    throw std::invalid_argument("Array must contain at least two numbers.");
  }

  // Initialize variables to track the two largest and two smallest numbers
  // Maximums - initialize to the smallest possible integer
  int largestNumber = std::numeric_limits<int>::min();
  int secondLargestNumber = std::numeric_limits<int>::min();
  // Minimums - initialize to the largest possible integer
  int smallestNumber = std::numeric_limits<int>::max();
  int secondSmallestNumber = std::numeric_limits<int>::max();

  // Iterate through the array to find the two largest and two smallest numbers,
  // while this has many single conditionals, it is still O(n) time complexity,
  // as we are only iterating through the array once
  for (int num : nums) {
    // Update the two largest numbers
    if (num > largestNumber) {
      // If the current number is greater than the largest number, then set the
      // current number as the largest, and move the previous largest to second
      // largest
      secondLargestNumber = largestNumber;
      largestNumber = num;
    } else if (num > secondLargestNumber) {
      // If the current number is not greater than the largest number but is
      // greater than the second largest, then set the second largest to the
      // current number
      secondLargestNumber = num;
    }

    // Update the two smallest numbers
    if (num < smallestNumber) {
      // If the current number is smaller than the smallest number, then set the
      // smallest number to the current number
      secondSmallestNumber = smallestNumber;
      smallestNumber = num;
    } else if (num < secondSmallestNumber) {
      // If the current number is not smaller than the smallest number but is
      // smaller than the second smallest, then set the second smallest to the
      // current number, set te smallest number to the current number
      secondSmallestNumber = num;
    }
  }

  // Returns the highest product of two numbers, which can be either:
  // 1. Product of the two largest numbers
  // 2. Product of the two smallest numbers (if both are negative)
  // The maximum of these two products is returned
  return std::max(largestNumber * secondLargestNumber,
                  smallestNumber * secondSmallestNumber);
}

int main() {
  std::vector<int> nums = {5, -10, -6, 9, 4};

  try {
    std::cout << "Highest product: " << highestProductOfTwo(nums) << std::endl;
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
