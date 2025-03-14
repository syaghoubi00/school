/**
 * advert_target_months.cpp
 *
 * Purpose: Analyzes monthly sales data to determine optimal advertising periods
 * The program finds the best consecutive months for sales and recommends
 * advertising periods before and after high sales seasons.
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

/**
 * Enum to define sorting methods for sales combinations
 * AVERAGE_SALES: Sort by average monthly sales (default)
 * TOTAL_SALES: Sort by total sales across the period
 */
enum class SortMethod { AVERAGE_SALES, TOTAL_SALES };

/**
 * Structure to hold parsed command line options
 * Contains sorting method preference, input filename, and help flag
 */
struct ProgramOptions {
  SortMethod sortMethod;
  std::string filename;
  bool helpRequested;
};

/**
 * Structure to store a single month's sales data
 * month: Name of the month (e.g., "Jan", "Feb")
 * sales: Sales amount in millions USD
 */
struct MonthlySales {
  std::string month;
  double sales;
};

/**
 * Structure to store the best sales period found
 * maxAvgSales: Best average monthly sales
 * maxAvgSalesStart: Index of the starting month for best period
 * maxAvgSalesLength: Number of consecutive months in best period
 * totalSales: Total sales across the best period
 */
struct SalesResult {
  double maxAvgSales;
  int maxAvgSalesStart;
  int maxAvgSalesLength;
  double totalSales;
};

/**
 * Structure to represent a specific combination of consecutive months
 * startMonth: Index of the first month in the combination
 * length: Number of consecutive months
 * totalSales: Sum of sales across all months in the combination
 * avgSales: Average monthly sales across the combination
 */
struct SalesCombination {
  int startMonth;
  int length;
  double totalSales;
  double avgSales;
};

/**
 * Reads sales data from a CSV or similar formatted file
 *
 * @param filename The path to the file to read
 * @return Optional vector of MonthlySales, empty if file can't be opened
 */
std::optional<std::vector<MonthlySales>>
readSalesDataFromFile(const std::string &filename) {
  std::vector<MonthlySales> data;
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return std::nullopt;
  }

  std::string line;
  // Skip header line (assumes first line is a header)
  std::getline(file, line);

  // Read each line and extract month name and sales amount
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

/**
 * Generates all possible consecutive month combinations and finds the best
 * period A "month combination" is a sequence of consecutive months, possibly
 * wrapping around the year
 *
 * @param salesData Vector of monthly sales data
 * @return Pair containing: 1) The best sales period found, 2) All possible
 * combinations
 */
std::pair<SalesResult, std::vector<SalesCombination>>
monthCombos(const std::vector<MonthlySales> &salesData) {

  SalesResult result;
  std::vector<SalesCombination> allCombinations;

  int n = salesData.size();

  // Initialize the result with default values
  result.maxAvgSales = 0;
  result.maxAvgSalesStart = 0;
  result.maxAvgSalesLength = 0;
  result.totalSales = 0;

  // For each possible starting month
  for (int start = 0; start < n; start++) {
    for (int length = 1; length < n; length++) {
      double totalSales = 0;

      // Calculate total sales for this combination of months
      for (int offset = 0; offset < length; offset++) {
        int idx =
            (start + offset) % n; // Wrap around using modulo for circular year
        totalSales += salesData[idx].sales;
      }

      // Calculate average monthly sales for this period
      double avgSales = totalSales / length;

      // We only consider periods longer than 1 month for the best period
      // Single months aren't as interesting for advertising strategy
      if (length > 1 && avgSales > result.maxAvgSales) {
        // Found a better average - update our best result
        result.maxAvgSales = avgSales;
        result.maxAvgSalesStart = start;
        result.maxAvgSalesLength = length;
        result.totalSales = totalSales;
      }
      // If we have equal average but longer consecutive period, prefer the
      // longer one
      else if (avgSales == result.maxAvgSales &&
               length > result.maxAvgSalesLength) {
        result.maxAvgSales = avgSales;
        result.maxAvgSalesStart = start;
        result.maxAvgSalesLength = length;
        result.totalSales = totalSales;
      }

      // Store this combination in our list of all combinations
      allCombinations.push_back({start, length, totalSales, avgSales});
    }
  }

  return {result, allCombinations};
}

/**
 * Sorts and displays sales combinations according to specified sort method
 *
 * @param allCombinations Vector of all month combinations to sort
 * @param salesData Original monthly sales data (for month names)
 * @param sortMethod Method to use for sorting (AVERAGE_SALES or TOTAL_SALES)
 */
void sortedMonthSales(const std::vector<SalesCombination> &allCombinations,
                      const std::vector<MonthlySales> &salesData,
                      SortMethod sortMethod) {

  // Make local copy to sort (since input is const)
  std::vector<SalesCombination> sortedCombinations = allCombinations;

  // Sort all combinations based on the specified sort method
  if (sortMethod == SortMethod::AVERAGE_SALES) {
    // Sort by average sales, highest first
    std::sort(sortedCombinations.begin(), sortedCombinations.end(),
              [](const SalesCombination &a, const SalesCombination &b) {
                return a.avgSales > b.avgSales;
              });
    std::cout << "Sorted Combinations by Average Sales (Highest to Lowest):"
              << std::endl;
  } else { // SortMethod::TOTAL_SALES
    // Sort by total sales, highest first
    std::sort(sortedCombinations.begin(), sortedCombinations.end(),
              [](const SalesCombination &a, const SalesCombination &b) {
                return a.totalSales > b.totalSales;
              });
    std::cout << "Sorted Combinations by Total Sales (Highest to Lowest):"
              << std::endl;
  }

  std::cout << "--------------------------------------------------------"
            << std::endl;

  // Display the sorted combinations
  for (int i = 0; i < sortedCombinations.size(); i++) {
    const auto &combo = sortedCombinations[i];

    std::cout << i + 1 << ". ";
    // Print the months in this combination
    for (int j = 0; j < combo.length; j++) {
      // Calculate the actual month index, handling wrap-around
      int idx = (combo.startMonth + j) % salesData.size();
      std::cout << salesData[idx].month;
      if (j < combo.length - 1) {
        std::cout << "-"; // Add separator between months
      }
    }

    // Display the sales metrics for this combination
    std::cout << ": Avg Sales = " << combo.avgSales << " million USD"
              << ", Total Sales = " << combo.totalSales << " million USD"
              << ", Length = " << combo.length << " months" << std::endl;
  }
}

/**
 * Displays detailed information about the best sales period found
 *
 * @param salesData Original monthly sales data (for month names)
 * @param result The best sales period result to display
 */
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
    // Calculate the actual month index, handling wrap-around
    int idx = (result.maxAvgSalesStart + i) % salesData.size();
    std::cout << salesData[idx].month;
    if (i < result.maxAvgSalesLength - 1) {
      std::cout << "-"; // Add separator between months
    }
  }
  std::cout << std::endl;
}

/**
 * Provides advertising recommendations based on analysis
 * Recommends targeting months before and after high sales periods
 *
 * @param salesData Original monthly sales data (for month names)
 * @param result The best sales period result to use for recommendations
 */
void recommendation(const std::vector<MonthlySales> &salesData,
                    SalesResult result) {
  // Advertising recommendations
  std::cout << "Advertising Recommendations:" << std::endl;
  std::cout << "--------------------------------" << std::endl;

  // Month before the best period - good for pre-season advertising
  int beforeIdx =
      (result.maxAvgSalesStart - 1 + salesData.size()) % salesData.size();
  std::cout << "Target BEFORE high sales: " << salesData[beforeIdx].month
            << std::endl;

  // Month after the best period - good for clearing inventory or early-bird
  // offers
  int afterIdx =
      (result.maxAvgSalesStart + result.maxAvgSalesLength) % salesData.size();
  std::cout << "Target AFTER high sales: " << salesData[afterIdx].month
            << std::endl;
}

/**
 * Parse command line arguments and return options
 *
 * @param argc Count of arguments
 * @param argv Array of argument strings
 * @return Structure containing parsed options
 */
ProgramOptions parseArguments(int argc, char *argv[]) {
  ProgramOptions options;

  // Set default values
  options.sortMethod = SortMethod::AVERAGE_SALES;
  options.helpRequested = false;

  // Process each command line argument
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];

    if (arg.rfind("--sort=", 0) == 0) {
      // --sort=method format (e.g., --sort=total)
      std::string sortMethodStr = arg.substr(7); // Skip "--sort="
      if (sortMethodStr == "total") {
        options.sortMethod = SortMethod::TOTAL_SALES;
      } else if (sortMethodStr == "average") {
        options.sortMethod = SortMethod::AVERAGE_SALES;
      } else {
        std::cout << "Unknown sort method: " << sortMethodStr << std::endl;
        std::cout << "Valid methods are: 'total', 'average'" << std::endl;
        options.helpRequested = true;
      }
    } else if (arg == "--sort" && i + 1 < argc) {
      // --sort followed by method name (e.g., --sort total)
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
      // Help flag
      options.helpRequested = true;
    } else if (arg == "--file" && i + 1 < argc) {
      // --file flag followed by filename
      options.filename =
          argv[++i]; // Move to the next argument and use it as filename
    } else if (arg.rfind("--file=", 0) == 0) {
      // --file=filename format
      options.filename = arg.substr(7); // Skip "--file="
    } else if (arg[0] == '-') {
      // Unknown flag
      std::cout << "Unknown option: " << arg << std::endl;
      options.helpRequested = true; // Trigger help display for unknown options
    } else {
      // Assume it's a filename (positional argument)
      options.filename = arg;
    }
  }

  return options;
}

/**
 * Displays usage information and help text
 *
 * @param programName Name of the executable (typically argv[0])
 */
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

/**
 * Main program entry point
 * Processes command line arguments, analyzes sales data, and displays results
 */
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
    // Default monthly sales data for testing
    salesData = {{"Jan", 100}, {"Feb", 113}, {"Mar", 110}, {"Apr", 85},
                 {"May", 81},  {"Jun", 101}, {"Jul", 94},  {"Aug", 106},
                 {"Sep", 105}, {"Oct", 102}, {"Nov", 86},  {"Dec", 63}};
  }

  // Get the result from monthCombos - both best period and all combinations
  auto [result, allCombinations] = monthCombos(salesData);

  // Display sorted sales combinations based on selected sort method
  sortedMonthSales(allCombinations, salesData, options.sortMethod);
  std::cout << std::endl;

  // Display detailed information about best sales period found
  bestSalesPeriod(salesData, result);
  std::cout << std::endl;

  // Display advertising recommendations
  recommendation(salesData, result);

  return 0;
};
