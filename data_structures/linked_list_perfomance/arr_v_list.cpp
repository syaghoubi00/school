#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

struct PerformanceResult {
  std::string name;
  int size;
  long duration;
};

std::vector<PerformanceResult> results;

template <typename Func>
void time(Func func, const std::string &name, int size) {
  std::cout << name << "..." << std::endl;
  auto start = std::chrono::high_resolution_clock::now();
  func(size);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  results.push_back({name, size, duration});
}

/* ARRAYS */
void addArrBeginning(const int size) {
  int *arr = new int[size];

  for (int i = 0; i < size; i++) {
    for (int j = i; j > 0; j--) {
      arr[j] = arr[j - 1];
    }
    arr[0] = i;
  }

  delete[] arr;
}
void addArrEnd(const int size) {
  int *arr = new int[size];

  for (int i = 0; i < size; i++) {
    arr[i] = i;
  };

  delete[] arr;
};
void removeArrBeginning(const int size) {
  int *arr = new int[size];
  for (int i = 0; i < size; i++) {
    arr[i] = i;
  }

  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - 1; j++) {
      arr[j] = arr[j + 1];
    }
  }

  delete[] arr;
}
void removeArrEnd(const int size) {
  // First create the array
  int *arr = new int[size];
  for (int i = 0; i < size; i++) {
    arr[i] = i;
  }

  for (int i = size - 1; i >= 0; i--) {
    arr[i] = -1;
  }

  delete[] arr;
}

/* LISTS */
void addListBeginning(const int size) {
  std::list<int> list;

  for (int i = 0; i < size; i++) {
    list.push_front(i);
  }
}
void addListEnd(const int size) {
  std::list<int> list;
  for (int i = 0; i < size; i++) {
    list.push_back(i);
  }
}
void removeListBeginning(const int size) {
  std::list<int> list;
  for (int i = 0; i < size; i++) {
    list.push_back(i);
  }

  while (!list.empty()) {
    list.pop_front();
  }
}
void removeListEnd(const int size) {
  std::list<int> list;
  for (int i = 0; i < size; i++) {
    list.push_back(i);
  }

  while (!list.empty()) {
    list.pop_back();
  }
}

void printResults() {
  std::cout << "Performance Results:" << std::endl;
  for (const auto &result : results) {
    std::cout << result.name << " with " << result.size
              << " elements: " << result.duration << " ms" << std::endl;
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
  csvFile << "Name,Size,Duration(ms)" << std::endl;

  // Write each result
  for (const auto &result : results) {
    csvFile << result.name << "," << result.size << "," << result.duration
            << std::endl;
  }

  csvFile.close();
  std::cout << "Results saved to " << filename << std::endl;
}

int main() {
  std::string addBeg = "Add to Beginning of ";
  std::string addEnd = "Add to End of ";
  std::string removeBeg = "Remove from Beginning of ";
  std::string removeEnd = "Remove from End of ";

  const int MILLION = 1000000;
  int small = 100 * MILLION;
  int medium = 200 * MILLION;
  int large = 300 * MILLION;

  for (int size : {small, medium, large}) {
    std::cout << "==== Testing with " << size << " elements ====" << std::endl;

    std::cout << "=== Adding to Beginning ===" << std::endl;
    time(addArrBeginning, addBeg + "Array", size);
    time(addListBeginning, addBeg + "List", size);

    std::cout << "=== Adding to End ===" << std::endl;
    time(addArrEnd, addEnd + "Array", size);
    time(addListEnd, addEnd + "List", size);

    std::cout << "=== Removing from Beginning ===" << std::endl;
    time(removeArrBeginning, removeBeg + "Array", size);
    time(removeListBeginning, removeBeg + "List", size);

    std::cout << "=== Removing from End ===" << std::endl;
    time(removeArrEnd, removeEnd + "Array", size);
    time(removeListEnd, removeEnd + "List", size);
  }

  printResults();

  saveResultsToCSV("performance_results.csv");

  return 0;
}
