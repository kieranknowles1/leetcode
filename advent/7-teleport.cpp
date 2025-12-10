#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <optional>
#include <string_view>
#include <vector>

#include "utils.hpp"

constexpr char Source = 'S';
constexpr char Splitter = '^';
constexpr char Beam = '|';
constexpr char Empty = '.';

void iterate(std::string_view current, std::string &next, int &splits) {
  assert(current.size() == next.size());

  auto split = [&](int to) {
    if (to < 0 || to >= next.length())
      return false;

    if (next[to] != Empty)
      return false;

    next[to] = Beam;
    return true;
  };

  for (int i = 0; i < next.size(); i++) {
    if (current[i] != Source && current[i] != Beam)
      continue;

    if (next[i] == Splitter) {
      bool left = split(i - 1);
      bool right = split(i + 1);
      if (left || right)
        splits++;
    } else {
      next[i] = Beam;
    }
  }
}

int beamSplits(std::filesystem::path file) {
  auto lines = readlines(file, '\n');

  int splits = 0;
  for (int i = 0; i < lines.size() - 1; i++) {
    iterate(lines[i], lines[i + 1], splits);
    std::cout << lines[i] << std::endl;
  }
  return splits;
}

int main() {
  uint64_t res = beamSplits("assets/7/example.txt");
  std::cout << res << " expected 21" << std::endl;

  res = beamSplits("assets/7/input.txt");
  std::cout << "Total: " << res << std::endl;
}
