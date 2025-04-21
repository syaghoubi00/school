#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

std::vector<std::string> parseNamesFromFile(const std::string &filename) {
  std::vector<std::string> names;
  std::ifstream file(filename);
  std::string line;

  if (file.is_open()) {
    std::cout << "Reading names from file: " << filename << std::endl;
    while (std::getline(file, line)) {
      names.push_back(line);
    }
    file.close();
  } else {
    std::cerr << "Unable to open file: " << filename << std::endl;
  }

  return names;
}

std::vector<int> loopEval(const std::vector<std::string> &authorsList,
                          const int iterations) {
  std::vector<int> loopResults;

  for (int i = 0; i < iterations; i++) {
    auto forLoopStart =
        std::chrono::high_resolution_clock::now(); // Start timing
    for (int i = 0; i < authorsList.size(); i++) {
      auto authorName = authorsList[i];
    }
    auto forLoopEnd = std::chrono::high_resolution_clock::now(); // End timing

    auto forLoopDuration =
        std::chrono::duration_cast<std::chrono::microseconds>(forLoopEnd -
                                                              forLoopStart)
            .count();

    loopResults.push_back(forLoopDuration);
  }

  return loopResults;
}

std::vector<int> iterEval(const std::vector<std::string> &authorsList,
                          const int iterations) {
  std::vector<int> loopResults;

  for (int i = 0; i < iterations; i++) {
    auto iterLoopStart =
        std::chrono::high_resolution_clock::now(); // Start timing
    auto iter = authorsList.begin();
    while (iter != authorsList.end()) {
      auto authorName = *iter;
      iter++;
    }
    auto iterLoopEnd = std::chrono::high_resolution_clock::now(); // End timing
    auto iterLoopDuration =
        std::chrono::duration_cast<std::chrono::microseconds>(iterLoopEnd -
                                                              iterLoopStart)
            .count();

    loopResults.push_back(iterLoopDuration);
  }

  return loopResults;
}

double calculateMean(const std::vector<int> &values) {
  double sum = std::accumulate(values.begin(), values.end(), 0.0);
  return sum / values.size();
}

double calculateStandardDeviation(const std::vector<int> &values) {
  double mean = calculateMean(values);
  double variance = 0.0;
  for (double value : values) {
    variance += (value - mean) * (value - mean);
  }
  variance /= values.size();
  return std::sqrt(variance);
}

void analyzeResults(const std::vector<int> &results) {
  double mean = calculateMean(results);
  double stdDev = calculateStandardDeviation(results);

  std::cout << "Mean: " << mean << " microseconds" << std::endl;
  std::cout << "Standard Deviation: " << stdDev << " microseconds" << std::endl;
}

int main() {
  std::string filename = "names.txt";
  std::vector<std::string> authorsList = parseNamesFromFile(filename);
  std::cout << "Number of authors: " << authorsList.size() << std::endl;

  const int iterations = 10000;
  std::cout << "Running " << iterations << " iterations..." << std::endl;

  std::cout << "Starting for loop..." << std::endl;
  std::vector<int> loopResults = loopEval(authorsList, iterations);
  std::cout << "Finished for loop." << std::endl;

  std::cout << "Starting iterator loop..." << std::endl;
  std::vector<int> iterResults = iterEval(authorsList, iterations);
  std::cout << "Finished iterator loop." << std::endl;

  std::cout << "Finished all iterations." << std::endl;

  std::cout << "Analyzing results..." << std::endl;
  std::cout << "For Loop Results:" << std::endl;
  analyzeResults(loopResults);
  std::cout << "Iterator Loop Results:" << std::endl;
  analyzeResults(iterResults);
}
