#include "util/prelude.hpp"

class Solution {
public:
  bool isValid(string s) {

    // An odd number of characters can't possibly be valid
    if (s.length() % 2 == 1)
      return false;
    std::stack<char> closes;
    auto validate = [&](char next) {
      if (closes.empty())
        return false; // No opening brace
      char expected = closes.top();
      closes.pop();
      return next == expected;
    };

    for (int i = 0; i < s.length(); i++) {
      char found = s[i];
      switch (found) {
      case '(':
        closes.push(')');
        break;
      case '{':
        closes.push('}');
        break;
      case '[':
        closes.push(']');
        break;
      case ')':
      case '}':
      case ']':
        if (!validate(found))
          return false;
        break;

      default:
        return false;
      }
    }

    // Check if all braces were closed
    return closes.empty();
  }
};

TestCases<string, bool> TEST_CASES = {
    {"()", true},    {"()[]{}", true}, {"(]", false}, {"([])", true},
    {"([)]", false}, {"((", false},    {"){", false}};

int main() {
  runTests<string, bool>(TEST_CASES, [](string input) {
    Solution solution;
    return solution.isValid(input);
  });
}
