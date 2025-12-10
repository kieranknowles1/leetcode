#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <map>
#include <vector>

#include "utils.hpp"

constexpr char Source = 'S';
constexpr char Splitter = '^';
constexpr char Beam = '|';
constexpr char Empty = '.';

struct Solver {
  std::vector<std::string> lines;
  std::map<Vector2, uint64_t> cache;

  void printBoard() {
    for (auto &line : lines) {
      std::cout << line << std::endl;
    }
  }

  uint64_t evalTimelines(Vector2 from) {
    if (from.x < 0 || from.x >= lines[from.y].length())
      return 0; // Out of bounds
    if (from.y + 1 >= lines.size())
      return 1; // Last row
    char c = lines[from.y][from.x];
    assert(c == Empty || c == Source);
    lines[from.y][from.x] = Beam;

    char down = lines[from.y + 1][from.x];
    if (down == Empty || down == Beam)
      return timelines({from.x, from.y + 1});
    else if (down == Splitter) {
      return timelines({from.x - 1, from.y + 1}) +
             timelines({from.x + 1, from.y + 1});
    }
    assert(false && "Should be unreachable");
    return -1;
  }

  uint64_t timelines(Vector2 from) {
    auto cacheHit = cache.find(from);
    if (cacheHit != cache.end())
      return cacheHit->second;

    uint64_t val = evalTimelines(from);
    cache[from] = val;
    return val;
  }

  uint64_t totalSplits() {
    uint64_t total = 0;
    for (int x = 0; x < lines[0].size(); x++) {
      if (lines[0][x] == Source) {
        total += timelines({x, 0});
      }
    }
    printBoard();
    return total;
  }
};

uint64_t beamSplits(std::filesystem::path file) {
  auto lines = readlines(file, '\n');
  Solver solver(lines);

  return solver.totalSplits();
}

int main() {
  uint64_t res = beamSplits("assets/7/example.txt");
  std::cout << res << " expected 40" << std::endl;

  res = beamSplits("assets/7/input.txt");
  std::cout << "Total: " << res << std::endl;
}
