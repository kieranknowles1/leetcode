#include "util/prelude.hpp"
#include <tuple>
#include <vector>

class Solution {
public:
  bool searchMatrix(vector<vector<int>> &matrix, int target) {
    // Find which row we're on, defaulting to the last
    int rowNum = matrix.size() - 1;
    for (int i = 1; i < matrix.size(); i++) {
      if (matrix[i][0] > target) {
        rowNum = i - 1;
        break;
      }
    }

    for (int i = 0; i < matrix[rowNum].size(); i++) {
      if (matrix[rowNum][i] == target)
        return true;
    }

    return false;
  }
};

using Matrix = vector<vector<int>>;
int main() {
  Solution s;
  Matrix case1 = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
  check(1, s.searchMatrix(case1, 3) == true);

  Matrix case2 = {{1}};
  check(2, s.searchMatrix(case2, 0) == false);

  return 0;
}
