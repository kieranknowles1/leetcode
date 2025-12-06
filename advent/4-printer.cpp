#include <cmath>
#include <cstdint>
#include <iostream>
#include <optional>
#include <string_view>

#include "utils.hpp"

constexpr char Empty = '.';
constexpr char Full = '@';
constexpr char Taken = 'x';
constexpr int MaxAdjacent = 3;

bool accessable(std::optional<std::string_view> previous,
                std::string_view current, std::optional<std::string_view> next,
                int x) {
  int used = 0;

  auto countRolls = [&](std::string_view line) {
    if (x > 0 && line[x - 1] == Full)
      used++;
    if (line[x] == Full)
      used++;
    if (x < line.length() - 1 && line[x + 1] == Full)
      used++;
    return std::optional<int>(std::nullopt);
  };

  previous.and_then([&](auto prev) { return countRolls(prev); });
  countRolls(current);
  next.and_then([&](auto next) { return countRolls(next); });
  // +1 as we count the current roll
  return used <= MaxAdjacent + 1;
}

int availableRolls(std::filesystem::path file) {
  auto lines = readlines(file, '\n');

  // How many rolls were taken at the end of the previous pass?
  int prevPass = 0;
  // How many rolls have been taken thus far?
  int available = 0;

  do {
    prevPass = available;

    for (int y = 0; y < lines.size(); y++) {
      auto prev = y > 0 ? std::optional(lines[y - 1]) : std::nullopt;
      auto next =
          y < lines.size() - 1 ? std::optional(lines[y + 1]) : std::nullopt;
      auto curr = lines[y];
      for (int x = 0; x < lines[y].size(); x++) {
        if (lines[y][x] == Full && accessable(prev, curr, next, x)) {
          available++;
          lines[y][x] = Taken;
        }
      }
      std::cout << lines[y] << std::endl;
    }

    std::cout << std::endl;
  } while (available > prevPass);

  return available;
}

int main() {
  uint64_t res = availableRolls("assets/4/example.txt");
  std::cout << res << " expected 13" << std::endl;

  res = availableRolls("assets/4/input.txt");
  std::cout << "Total: " << res << std::endl;
}
