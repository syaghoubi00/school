#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

int longestConsecutiveSequence(const std::vector<int> &nums) {
  // Use an unordered_set to store all numbers for fast lookups
  std::unordered_set<int> numSet(nums.begin(), nums.end());
  int longestStreak = 0; // Variable to track the longest consecutive sequence

  // Iterate through each number in the hash set O(n)
  for (int num : numSet) {
    // Check if the current number is the start of a sequence
    // A number is the start if there is no (num - 1) in the set
    // If there is (num - 1), it means this number is part of a longer sequence,
    // so we skip it, as we only want to count the start of sequences.
    // O(1) lookup time for unordered_set
    if (numSet.find(num - 1) == numSet.end()) {
      int currentNum = num;  // Start of the sequence
      int currentStreak = 1; // Initialize the streak length to 1

      // Continue checking for the next consecutive numbers
      // Added time complexity would be the length of the sequence
      while (numSet.find(currentNum + 1) != numSet.end()) {
        currentNum++;    // Move to the next number in the sequence
        currentStreak++; // Increment the streak length
      }

      // Update the longest streak if the current streak is longer
      longestStreak = std::max(longestStreak, currentStreak);
    }
  }

  // Return the length of the longest consecutive sequence
  return longestStreak;
}

int main() {
  // Arrays from the task
  std::vector<int> nums1 = {10, 5, 12, 3, 55, 30, 4, 11, 2};
  std::vector<int> nums2 = {19, 13, 15, 12, 18, 14, 17, 11};

  std::cout << "Longest consecutive sequence in nums1: "
            << longestConsecutiveSequence(nums1) << std::endl;
  std::cout << "Longest consecutive sequence in nums2: "
            << longestConsecutiveSequence(nums2) << std::endl;

  return 0;
}
