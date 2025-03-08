#include <functional> // for std::hash - provides the hash function template
#include <iostream>
#include <string>

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

int main() {

  std::string input = userInput();
  std::cout << "---" << std::endl;

  std::cout << "Task 2:" << std::endl;
  hashInput(input);
  std::cout << "---" << std::endl;

  return 0;
}
