#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

struct Player {
  std::string first_name;
  std::string last_name;
  std::string team;
};

std::vector<std::string>
findCommonPlayers(const std::vector<Player> &basketball_players,
                  const std::vector<Player> &football_players) {
  std::unordered_set<std::string> basketball_set;
  std::vector<std::string> common_players;

  // Step 1: Add full names of basketball players to the set
  // O(n) operation, adding n names to the set
  for (const auto &player : basketball_players) {
    basketball_set.insert(player.first_name + " " + player.last_name);
  }

  // Step 2: Check football players against the set
  // O(n) operation, checking n names against the set
  for (const auto &player : football_players) {
    std::string full_name = player.first_name + " " + player.last_name;
    if (basketball_set.find(full_name) != basketball_set.end()) {
      common_players.push_back(full_name);
    }
  }

  // Since the two O(n) operations are sequential, we get O(n+n) instead of the
  // O(n*n) with a nested loop

  // Returns a vector of common player names
  return common_players;
}

int main() {
  std::vector<Player> basketball_players = {{"Jill", "Huang", "Gators"},
                                            {"Janko", "Barton", "Sharks"},
                                            {"Wanda", "Vakulskas", "Sharks"},
                                            {"Jill", "Moloney", "Gators"},
                                            {"Luuk", "Watkins", "Gators"}};

  std::vector<Player> football_players = {
      {"Hanzla", "Radosti", "32ers"},
      {"Tina", "Watkins", "Barleycorns"},
      {"Alex", "Patel", "32ers"},
      {"Jill", "Huang", "Barleycorns"},
      {"Wanda", "Vakulskas", "Barleycorns"}};

  std::vector<std::string> common_players =
      findCommonPlayers(basketball_players, football_players);

  // Output the common players
  // O(n) operation, printing n names of common players
  for (const auto &name : common_players) {
    std::cout << name << std::endl;
  }

  return 0;
}
