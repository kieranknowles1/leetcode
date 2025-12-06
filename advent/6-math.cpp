#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <optional>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

#include "utils.hpp"

constexpr char Empty = '.';
constexpr char Full = '@';
constexpr char Taken = 'x';
constexpr int MaxAdjacent = 3;

int64_t solveProblem(std::vector<std::string> problem) {
  char op = problem[problem.size() - 1][0];

  int64_t total = op == '+' ? 0 : 1;
  for (int i = 0; i < problem.size() - 1; i++) {
    int64_t val = std::stoll(problem[i]);
    switch (op) {
    case '+':
      total += val;
      break;
    case '*':
      total *= val;
      break;
    default:
      assert(false);
    }
  }

  return total;
}

int64_t mathTotal(std::filesystem::path file) {
  auto lines = readlines(file, '\n');
  std::vector<std::vector<std::string>> columns;

  // Dirty way to transpose columns
  for (auto line : lines) {
    std::regex rgx(" +");
    std::sregex_token_iterator iter(line.begin(), line.end(), rgx, -1);
    std::sregex_token_iterator end;

    int x = 0;
    for (; iter != end; ++iter) {
      std::string str = *iter;
      if (str.empty())
        continue;

      if (x >= columns.size())
        columns.emplace_back();

      columns[x].emplace_back(str);
      x++;
    }
  }

  int64_t sum = 0;
  for (auto &column : columns) {
    sum += solveProblem(column);
  }

  return sum;
}

int main() {
  uint64_t res = mathTotal("assets/6/example.txt");
  std::cout << res << " expected 4277556" << std::endl;

  res = mathTotal("assets/6/input.txt");
  std::cout << "Total: " << res << std::endl;
}
