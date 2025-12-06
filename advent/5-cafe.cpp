#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <optional>
#include <string_view>
#include <vector>

#include "utils.hpp"

class FreshDb {
public:
  FreshDb(std::vector<std::string> &database) {
    std::vector<Range> tmp;
    for (auto &line : database) {
      if (line.empty())
        break;
      tmp.push_back(splitHyphens(line));
    }
    std::sort(tmp.begin(), tmp.end());

    while (!tmp.empty()) {

      int64_t groupBegin = tmp[0].begin;
      int64_t groupEnd = tmp[0].end;

      int groupEndIdx = tmp.size();
      std::cout << "grp" << std::endl;
      tmp[0].print();
      for (int i = 1; i < tmp.size(); i++) {
        // Overlap
        if (tmp[i].begin <= groupEnd) {
          tmp[i].print();
          groupEnd = std::max(groupEnd, tmp[i].end);
        } else {
          groupEndIdx = i;
          break;
        }
      }

      ranges.emplace_back(Range(groupBegin, groupEnd));
      tmp.erase(tmp.begin(), tmp.begin() + groupEndIdx);
      ranges[ranges.size() - 1].print();
    }

    // for (int i = 0; i < tmp.size(); i++) {
    //   int groupEnd = i;

    //   ranges.push_back(tmp[i]);
    // }
  }

  bool fresh(int64_t ingredient) {
    for (auto range : ranges) {
      if (ingredient >= range.begin && ingredient <= range.end)
        return true;
    }
    return false;
  }

  int64_t totalFresh() {
    int64_t total = 0;

    std::cout << "total" << std::endl;
    for (auto &range : ranges) {
      range.print();

      total += range.end - range.begin;
      // +1 for end
      if (range.begin != range.end)
        total++;
    }

    return total;
  }

private:
  std::vector<Range> ranges;
};

int64_t freshIngredients(std::filesystem::path file) {
  auto lines = readlines(file, '\n');
  FreshDb db(lines);

#if false
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
#endif

  return db.totalFresh();
}

int main() {
  uint64_t res = freshIngredients("assets/5/example.txt");
  std::cout << res << " expected 14" << std::endl;

  res = freshIngredients("assets/5/input.txt");
  std::cout << "Total: " << res << std::endl;
}
