#include <functional> // for std::hash - provides the hash function template
#include <iostream>
#include <string>
#include <unordered_set>

std::string userInput() {
  std::string input;

  std::cout << "Enter a name: ";
  std::getline(std::cin, input);

  return input;
}

void hashInput(std::string in) {
  std::hash<std::string> strHasher;
  size_t hashValue = strHasher(in);

  std::cout << "Hash value of \"" << in << "\": " << hashValue << std::endl;
}

void bounus_task(std::string in) {
  // Create an unordered set of strings
  std::unordered_set<std::string> names;

  names.insert("Alice");
  names.insert("Bob");

  if (names.find(in) != names.end()) {
    std::cout << in << " is in the set!" << std::endl;
  } else {
    std::cout << in << " is not in the set." << std::endl;
    std::cout << "Adding " << in << " to the set." << std::endl;
    names.insert(in);
    std::cout << in << " has been added to the set." << std::endl;
  }

  std::cout << "Set contents:" << std::endl;
  for (const auto &name : names) {
    std::cout << name << std::endl;
  }
}

int main() {

  std::string input = userInput();
  std::cout << "---" << std::endl;

  std::cout << "Task 2:" << std::endl;
  hashInput(input);
  std::cout << "---" << std::endl;

  std::cout << "Bonus Task:" << std::endl;
  bounus_task(input);

  return 0;
}
