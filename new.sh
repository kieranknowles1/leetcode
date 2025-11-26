#!/usr/bin/env bash
set -euo pipefail

OUTFILE="src/$1.cpp"

echo "$OUTFILE" >> sources.txt

cat <<EOF > "$OUTFILE"
#include "util/prelude.hpp"

using TIn = string;
using TOut = bool;
class Solution {
public:
  TOut isValid(TIn s) {

  }
};

TestCases<TIn, TOut> TEST_CASES = {};

int main() {
  runTests<TIn, TOut>(TEST_CASES, [](string input) {
    Solution solution;
    return solution.isValid(input);
  });
}
EOF

cmake build
