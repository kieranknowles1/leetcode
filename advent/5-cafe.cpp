#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <optional>
#include <string_view>

#include "utils.hpp"

class FreshDb {
public:
  FreshDb(std::vector<std::string> &database) {
    for (auto &line : database) {
      if (line.empty())
        break;
      ranges.push_back(splitHyphens(line));
    }
  }

  bool fresh(int64_t ingredient) {
    for (auto range : ranges) {
      if (ingredient >= range.begin && ingredient <= range.end)
        return true;
    }
    return false;
  }

private:
  std::vector<Range> ranges;
};

int freshIngredients(std::filesystem::path file) {
  auto lines = readlines(file, '\n');
  FreshDb db(lines);

  int availableStart = -1;
  for (int i = 0; i < lines.size(); i++) {
    if (lines[i].empty()) {
      availableStart = i + 1;
      break;
    }
  }
  assert(availableStart > 0);

  int fresh = 0;
  for (int i = availableStart; i < lines.size(); i++) {
    int64_t id = std::stoll(lines[i]);
    if (db.fresh(id))
      fresh++;
  }

  return fresh;
}

int main() {
  uint64_t res = freshIngredients("assets/5/example.txt");
  std::cout << res << " expected 3" << std::endl;

  res = freshIngredients("assets/5/input.txt");
  std::cout << "Total: " << res << std::endl;
}
