// Prelude that sets up a leetcode-like environment
// and provides utilites for testing

#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

template <typename TIn, typename TOut>
using TestCases = vector<pair<TIn, TOut>>;

template <typename TIn, typename TOut>
bool runTests(const TestCases<TIn, TOut> &testCases,
              function<TOut(TIn)> testFunc) {
  bool passed = true;
  for (const auto &testCase : testCases) {
    const auto &[input, expected] = testCase;
    bool result = testFunc(input) == expected;
    passed &= result;
    if (!result) {
      cout << "Test failed: input = " << input << ", expected = " << expected
           << ", actual = " << testFunc(input) << endl;
    }
  }
  return passed;
}
