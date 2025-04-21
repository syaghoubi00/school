#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <vector>

struct PerformanceResult {
  std::string name;
  size_t elements;
  size_t memoryGiB;
  long duration;
};

// Initialize a global vector to store performance results
std::vector<PerformanceResult> results;

template <typename Func, typename Container>
void time(const std::string name, Func func, Container &items) {
  // Start the timer
  std::chrono::time_point start = std::chrono::high_resolution_clock::now();

  // Run the function with the container
  func(items);

  // End the timer after function execution
  std::chrono::time_point end = std::chrono::high_resolution_clock::now();

  // Calculate the duration in microseconds
  long duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start)
          .count();

  size_t memoryInGiB =
      sizeof(items) + (items.size() * sizeof(typename Container::value_type)) /
                          (1024 * 1024 * 1024);

  // Push results to the global vector
  results.push_back({name, items.size(), memoryInGiB, duration});
}

/* ARRAYS */
void arrAddToBeg(std::vector<int> &vec) { vec.insert(vec.begin(), 0); }
void arrAddToEnd(std::vector<int> &vec) { vec.push_back(0); }
void arrRemoveFromBeg(std::vector<int> &vec) { vec.erase(vec.begin()); }
void arrRemoveFromEnd(std::vector<int> &vec) { vec.pop_back(); }

/* LISTS */
void listAddToBeg(std::list<int> &list) { list.push_front(0); }
void listAddToEnd(std::list<int> &list) { list.push_back(0); }
void listRemoveFromBeg(std::list<int> &list) { list.pop_front(); }
void listRemoveFromEnd(std::list<int> &list) { list.pop_back(); }

void printResults() {
  std::cout << "Performance Results:" << std::endl;
  for (const auto &result : results) {
    std::cout << result.name << " with " << result.elements << " elements "
              << "consumed " << std::fixed << std::setprecision(3)
              << result.memoryGiB << "GiB" << std::defaultfloat
              << " and took: " << result.duration << " microseconds"
              << std::endl;
  }
}

void saveResultsToCSV(const std::string &filename) {
  std::ofstream csvFile(filename);

  if (!csvFile.is_open()) {
    std::cerr << "Error: Could not open file " << filename << " for writing!"
              << std::endl;
    return;
  }

  // Write CSV header
  csvFile << "Name,Elements,Memory(GiB),Duration(microseconds)" << std::endl;

  // Write each result
  for (const auto &result : results) {
    csvFile << result.name << "," << result.elements << "," << result.memoryGiB
            << "," << result.duration << std::endl;
  }

  csvFile.close();
  std::cout << "Results saved to " << filename << std::endl;
}

int main() {
  std::string addBeg = "Adding to Beginning of ";
  std::string addEnd = "Adding to End of ";
  std::string removeBeg = "Removing from Beginning of ";
  std::string removeEnd = "Removing from End of ";

  const int MILLION = 1000000;

  int multiplier = MILLION;

  int small = 100 * multiplier;
  int medium = 200 * multiplier;
  int large = 300 * multiplier;

  // Test Arrays (vector)
  for (int size : {small, medium, large}) {
    std::string type = "Array";
    std::vector<int> vec;

    // Fill Vector
    for (int i = 0; i < size; i++) {
      vec.push_back(i);
    }

    std::cout << "Testing Array with " << size << " elements..." << std::endl;

    time(addBeg + type, arrAddToBeg, vec);
    time(addEnd + type, arrAddToEnd, vec);
    time(removeBeg + type, arrRemoveFromBeg, vec);
    time(removeEnd + type, arrRemoveFromEnd, vec);
  }

  // Test Lists (std::list)
  for (int size : {small, medium, large}) {
    std::string type = "List";
    std::list<int> list;

    // Fill List
    for (int i = 0; i < size; i++) {
      list.push_back(i);
    }

    std::cout << "Testing List with " << size << " elements..." << std::endl;

    time(addBeg + type, listAddToBeg, list);
    time(addEnd + type, listAddToEnd, list);
    time(removeBeg + type, listRemoveFromBeg, list);
    time(removeEnd + type, listRemoveFromEnd, list);
  }

  printResults();

  std::cout << "Saving results to CSV..." << std::endl;
  saveResultsToCSV("performance_results.csv");

  return 0;
}
