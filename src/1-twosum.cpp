#include "util/prelude.hpp"
#include <cassert>

#ifdef SOLUTION_A
// Runs in O(n^2) time and O(1) space
class Solution {
public:
  vector<int> twoSum(vector<int> &nums, int target) {
    vector<int> result;

    for (int x = 0; x < nums.size(); x++) {
      for (int y = x + 1; y < nums.size(); y++) {
        if (nums[x] + nums[y] == target) {
          result.push_back(x);
          result.push_back(y);
          return result;
        }
      }
    }
    assert(false);
  }
};
#endif

class Solution {
public:
  vector<int> twoSum(vector<int> &nums, int target) {
    // Number -> index in `nums`
    std::unordered_map<int, int> index;

    for (int i = 0; i < nums.size(); i++) {
      int compliment = target - nums[i];
      auto found = index.find(compliment);
      if (found != index.end()) {
        return {i, found->second};
      }
      index[nums[i]] = i;
    }

    assert(false);
  }
};
