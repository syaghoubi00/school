#include <array>
#include <iostream>
#include <vector>

// Function to sort temperature readings using counting sort O(n+k)
std::vector<float> sortTemperatures(const std::vector<float> &readings) {
  // Define the range of possible temperatures
  // Temperatures range from 97.0 to 99.0, inclusive, with one decimal place.
  const int rangeSize = 21;               // (99.0 - 97.0) * 10 + 1
  std::array<int, rangeSize> count = {0}; // Initialize count array to 0

  // Create the count array
  for (float temp : readings) {
    // Map the temperature to an index in the count array
    int index = static_cast<int>((temp - 97.0) * 10 + 0.5);
    count[index]++;
  }

  // Construct the sorted array
  std::vector<float> sortedReadings;
  for (int i = 0; i < rangeSize; ++i) {
    // Calculate the temperature corresponding to the current index
    float temperature = 97.0 + i * 0.1f;
    // Append the temperature to the sorted array based on its count
    for (int j = 0; j < count[i]; ++j) {
      sortedReadings.push_back(temperature);
    }
  }

  return sortedReadings;
}

int main() {
  // Sample temperature readings
  std::vector<float> readings = {98.6, 98.0, 97.1, 99.0, 98.9,
                                 97.8, 98.5, 98.2, 98.0, 97.1};

  // Sort the readings
  std::vector<float> sortedReadings = sortTemperatures(readings);

  // Output the sorted readings
  std::cout << "Sorted Temperatures: ";
  for (float temp : sortedReadings) {
    std::cout << temp << " ";
  }
  std::cout << std::endl;

  return 0;
}
