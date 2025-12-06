#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>

#include "utils.hpp"

bool substrRepeats(std::string_view idStr, int repetitions) {
  if (idStr.length() % repetitions != 0)
    return false;

  int subLength = idStr.length() / repetitions;
  assert(subLength * repetitions == idStr.length());

  for (int x = 0; x < subLength; x++) {
    char first = idStr[x];
    for (int y = 1; y < repetitions; y++) {
      char second = idStr[x + (subLength * y)];
      if (first != second)
        return false;
    }
  }

  return true;
}

bool productValid(int64_t id) {
  std::string str = std::to_string(id);

  for (int reps = 2; reps <= str.length(); reps++) {
    if (substrRepeats(str, reps)) {
      return false;
    }
  }
  return true;
}

int64_t invalidIdSum(std::filesystem::path file) {
  auto lines = readlines(file, ',');
  int64_t sum = 0;

  for (auto &line : lines) {
    auto range = splitHyphens(line);

    for (int64_t i = range.begin; i <= range.end; i++) {
      if (!productValid(i)) {
        sum += i;
      }
    }
  }

  return sum;
}

int main() {
  int64_t result = invalidIdSum("assets/2/example.txt");
  std::cout << "Sum of invalid IDs is " << result << " expected 4174379265"
            << std::endl;

  result = invalidIdSum("assets/2/input.txt");
  std::cout << "Sum of invalid IDs is " << result << std::endl;
}
