#include <cstdint>
#include <iostream>
#include <string>

#include "utils.hpp"

bool productValid(int64_t id) {
  std::string str = std::to_string(id);
  if (str.length() % 2 != 0)
    return true;

  for (int x = 0; x < str.length() / 2; x++) {
    int y = x + str.length() / 2;
    if (str[x] != str[y])
      return true;
  }

  return false;
}

int64_t invalidIdSum(std::filesystem::path file) {
  auto lines = readlines(file, ',');
  int64_t sum = 0;

  for (auto &line : lines) {
    std::string sstart = line.substr(0, line.find('-'));
    std::string send = line.substr(sstart.length() + 1, line.length());
    int64_t start = std::stoll(sstart);
    int64_t end = std::stoll(send);

    for (int64_t i = start; i <= end; i++) {
      if (!productValid(i)) {
        sum += i;
      }
    }
  }

  return sum;
}

int main() {
  int64_t result = invalidIdSum("assets/2/example.txt");
  std::cout << "Sum of invalid IDs is " << result << " expected 1227775554"
            << std::endl;

  result = invalidIdSum("assets/2/input.txt");
  std::cout << "Sum of invalid IDs is " << result << std::endl;
}
