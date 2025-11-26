#include "util/prelude.hpp"

class Solution {
public:
  bool isValid(string s) { return false; }
};

TestCases<string, bool> TEST_CASES = {{"()", true},
                                      {"()[]{}", true},
                                      {"(]", false},
                                      {"([])", true},
                                      {"([)]", false}};

int main() {
  function<bool(string)> t = [](string input) {
    Solution solution;
    return solution.isValid(input);
  };

  runTests<string, bool>(TEST_CASES, [](string input) {
    Solution solution;
    return solution.isValid(input);
  });
}
