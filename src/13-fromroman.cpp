#include "util/prelude.hpp"

using TIn = string;
using TOut = int;
class Solution {
public:
  int charValue(char c) {
    switch (c) {
    case 'I':
      return 1;
    case 'V':
      return 5;
    case 'X':
      return 10;
    case 'L':
      return 50;
    case 'C':
      return 100;
    case 'D':
      return 500;
    case 'M':
      return 1000;
    default:
      assert(false);
    }
  }

  bool subtracts(char c, char next) {
    if (c == 'I')
      return next == 'V' || next == 'X';
    if (c == 'X')
      return next == 'L' || next == 'C';
    if (c == 'C')
      return next == 'D' || next == 'M';
    return false;
  }

  int romanToInt(string s) {
    int total = 0;
    for (int i = 0; i < s.length(); i++) {
      int value = charValue(s[i]);
      if (i + 1 < s.length()) {
        if (subtracts(s[i], s[i + 1])) {
          value = -value;
        }
      }
      total += value;
    }
    return total;
  }
};

TestCases<TIn, TOut> TEST_CASES = {
    {"III", 3},
    {"IV", 4},
    {"LVIII", 58},
};

int main() {
  runTests<TIn, TOut>(TEST_CASES, [](string input) {
    Solution solution;
    return solution.romanToInt(input);
  });
}
