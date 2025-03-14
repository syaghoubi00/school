#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// Flag to determine sorting method
enum class SortMethod { AVERAGE_SALES, TOTAL_SALES };

// Structure to hold parsed command line options
struct ProgramOptions {
  SortMethod sortMethod;
  std::string filename;
  bool helpRequested;
};

struct MonthlySales {
  std::string month;
  double sales;
};

struct SalesResult {
  double maxAvgSales;
  int maxAvgSalesStart;
  int maxAvgSalesLength;
  double totalSales;
};

struct SalesCombination {
  int startMonth;
  int length;
  double totalSales;
  double avgSales;
};

std::optional<std::vector<MonthlySales>>
readSalesDataFromFile(const std::string &filename) {
  std::vector<MonthlySales> data;
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return std::nullopt;
  }

  std::string line;
  // Skip header line
  std::getline(file, line);

  // Read data lines
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string month;
    double sales;

    if (iss >> month >> sales) {
      data.push_back({month, sales});
    }
  }

  file.close();
  return data;
}

std::pair<SalesResult, std::vector<SalesCombination>>
monthCombos(const std::vector<MonthlySales> &salesData) {

  SalesResult result;
  std::vector<SalesCombination> allCombinations;

  int n = salesData.size();

  result.maxAvgSales = 0;
  result.maxAvgSalesStart = 0;
  result.maxAvgSalesLength = 0;
  result.totalSales = 0;

  // For each possible starting month
  for (int start = 0; start < n; start++) {
    for (int length = 1; length < n; length++) {
      double totalSales = 0;

      // Print the range of months
      for (int offset = 0; offset < length; offset++) {
        int idx = (start + offset) % n; // Wrap around using modulo
        // std::cout << salesData[idx].month;
        totalSales += salesData[idx].sales;

        // Add separator if not the last month in the combination
        // if (offset < length - 1) {
        //   std::cout << "-";
        // }
      }

      double avgSales = totalSales / length;

      // Exclude single month periods from the result, as the month with the
      // highest sales will always be the best
      if (length > 1 && avgSales > result.maxAvgSales) {
        result.maxAvgSales = avgSales;
        result.maxAvgSalesStart = start;
        result.maxAvgSalesLength = length;
        result.totalSales = totalSales;
      }
      // Use longer consecutive periods if they have the same average sales
      else if (avgSales == result.maxAvgSales &&
               length > result.maxAvgSalesLength) {
        result.maxAvgSales = avgSales;
        result.maxAvgSalesStart = start;
        result.maxAvgSalesLength = length;
        result.totalSales = totalSales;
      }

      // Store this combination
      allCombinations.push_back({start, length, totalSales, avgSales});
    }
  }

  return {result, allCombinations};
}

void sortedMonthSales(const std::vector<SalesCombination> &allCombinations,
                      const std::vector<MonthlySales> &salesData,
                      SortMethod sortMethod) {

  // Make local copy to sort
  std::vector<SalesCombination> sortedCombinations = allCombinations;

  // Sort all combinations based on the specified sort method
  if (sortMethod == SortMethod::AVERAGE_SALES) {
    std::sort(sortedCombinations.begin(), sortedCombinations.end(),
              [](const SalesCombination &a, const SalesCombination &b) {
                return a.avgSales > b.avgSales;
              });
    std::cout << "Sorted Combinations by Average Sales (Highest to Lowest):"
              << std::endl;
  } else { // SortMethod::TOTAL_SALES
    std::sort(sortedCombinations.begin(), sortedCombinations.end(),
              [](const SalesCombination &a, const SalesCombination &b) {
                return a.totalSales > b.totalSales;
              });
    std::cout << "Sorted Combinations by Total Sales (Highest to Lowest):"
              << std::endl;
  }

  std::cout << "--------------------------------------------------------"
            << std::endl;

  for (int i = 0; i < sortedCombinations.size(); i++) {
    const auto &combo = sortedCombinations[i];

    std::cout << i + 1 << ". ";
    // Print the months in this combination
    for (int j = 0; j < combo.length; j++) {
      int idx = (combo.startMonth + j) % salesData.size();
      std::cout << salesData[idx].month;
      if (j < combo.length - 1) {
        std::cout << "-";
      }
    }

    std::cout << ": Avg Sales = " << combo.avgSales << " million USD"
              << ", Total Sales = " << combo.totalSales << " million USD"
              << ", Length = " << combo.length << " months" << std::endl;
  }
}

void bestSalesPeriod(const std::vector<MonthlySales> &salesData,
                     SalesResult result) {
  // Display the best combination found
  std::cout << "Best sales period found:" << std::endl;
  std::cout << "--------------------------------" << std::endl;
  std::cout << "Starting month: " << salesData[result.maxAvgSalesStart].month
            << std::endl;
  std::cout << "Number of months: " << result.maxAvgSalesLength << std::endl;
  std::cout << "Total sales: " << result.totalSales << " million USD"
            << std::endl;
  std::cout << "Average monthly sales: " << result.maxAvgSales << " million USD"
            << std::endl;

  // Display the months in the best period
  std::cout << "Months: ";
  for (int i = 0; i < result.maxAvgSalesLength; i++) {
    int idx = (result.maxAvgSalesStart + i) % salesData.size();
    std::cout << salesData[idx].month;
    if (i < result.maxAvgSalesLength - 1) {
      std::cout << "-";
    }
  }
  std::cout << std::endl;
}

void recommendation(const std::vector<MonthlySales> &salesData,
                    SalesResult result) {
  // Advertising recommendations
  std::cout << "Advertising Recommendations:" << std::endl;
  std::cout << "--------------------------------" << std::endl;

  // Month before the best period
  int beforeIdx =
      (result.maxAvgSalesStart - 1 + salesData.size()) % salesData.size();
  std::cout << "Target BEFORE high sales: " << salesData[beforeIdx].month
            << std::endl;

  // Month after the best period
  int afterIdx =
      (result.maxAvgSalesStart + result.maxAvgSalesLength) % salesData.size();
  std::cout << "Target AFTER high sales: " << salesData[afterIdx].month
            << std::endl;
}

// Parse command line arguments and return options
ProgramOptions parseArguments(int argc, char *argv[]) {
  ProgramOptions options;

  // Set default values
  options.sortMethod = SortMethod::AVERAGE_SALES;
  options.helpRequested = false;

  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];

    if (arg.rfind("--sort=", 0) == 0) {
      // --sort=method format
      std::string sortMethodStr = arg.substr(7); // Skip "--sort="
      if (sortMethodStr == "total") {
        options.sortMethod = SortMethod::TOTAL_SALES;
      } else if (sortMethodStr == "average") {
        options.sortMethod = SortMethod::AVERAGE_SALES;
      } else {
        std::cout << "Unknown sort method: " << sortMethodStr << std::endl;
        std::cout << "Valid methods are: 'total', 'average'"

                  << std::endl;
        options.helpRequested = true;
      }
    } else if (arg == "--sort" && i + 1 < argc) {
      // --sort followed by method name
      std::string sortMethodStr = argv[++i];
      if (sortMethodStr == "total") {
        options.sortMethod = SortMethod::TOTAL_SALES;
      } else if (sortMethodStr == "average") {
        options.sortMethod = SortMethod::AVERAGE_SALES;
      } else {
        std::cout << "Unknown sort method: " << sortMethodStr << std::endl;
        std::cout << "Valid methods are: 'total', 'average'" << std::endl;
        options.helpRequested = true;
      }
    } else if (arg == "--help") {
      options.helpRequested = true;
    } else if (arg == "--file" && i + 1 < argc) {
      // --file flag followed by filename
      options.filename =
          argv[++i]; // Move to the next argument and use it as filename
    } else if (arg.rfind("--file=", 0) == 0) {
      // --file=filename format
      options.filename = arg.substr(7); // Skip "--file="
    } else if (arg[0] == '-') {
      std::cout << "Unknown option: " << arg << std::endl;
      options.helpRequested = true; // Trigger help display for unknown options
    } else {
      // Assume it's a filename (positional argument)
      options.filename = arg;
    }
  }

  return options;
}

void printUsage(const char *programName) {
  std::cout << "Usage: " << programName << " [options] [filename]" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  --sort=<method>   Specify sorting method: 'average' "
               "(default) or 'total'"
            << std::endl;
  std::cout << "  --sort <method>   Specify sorting method: 'average' "
               "(default) or 'total'"
            << std::endl;
  std::cout << "  --file=<path>     Specify the data file path" << std::endl;
  std::cout << "  --file <path>     Specify the data file path" << std::endl;
  std::cout << "  --help            Display this help message" << std::endl;
  std::cout << std::endl;
  std::cout << "You can also provide the filename as the last argument without "
               "any flag."
            << std::endl;
}

int main(int argc, char *argv[]) {

  // Parse command line arguments
  ProgramOptions options = parseArguments(argc, argv);

  // Handle help request
  if (options.helpRequested) {
    printUsage(argv[0]);
    return options.filename.empty() ? 0 : 1; // Return error if unknown option
  }

  std::cout << "Sales Data Analysis" << std::endl;
  std::cout << "-------------------" << std::endl;
  std::cout << std::endl;

  std::vector<MonthlySales> salesData;

  // Load sales data from file if provided
  auto salesDataOpt = readSalesDataFromFile(options.filename);
  if (!salesDataOpt) {
    std::cout << "Error loading data from file: " << options.filename
              << std::endl;
    std::cout << "Using default 2023 sales data instead." << std::endl;
    // Use default data
  } else {
    salesData = *salesDataOpt;
  }

  // If no file provided or file was empty, use the default data
  if (salesData.empty()) {
    salesData = {{"Jan", 100}, {"Feb", 113}, {"Mar", 110}, {"Apr", 85},
                 {"May", 81},  {"Jun", 101}, {"Jul", 94},  {"Aug", 106},
                 {"Sep", 105}, {"Oct", 102}, {"Nov", 86},  {"Dec", 63}};
  }

  // Get the result from monthCombos
  auto [result, allCombinations] = monthCombos(salesData);

  sortedMonthSales(allCombinations, salesData, options.sortMethod);
  std::cout << std::endl;
  bestSalesPeriod(salesData, result);
  std::cout << std::endl;
  recommendation(salesData, result);

  return 0;
};
