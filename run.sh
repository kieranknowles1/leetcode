#!/usr/bin/env bash
set -euo pipefail

testnum=$1
target=$(find ./src/ -name "$testnum-*.cpp" | sed -e 's|src/||' -e 's|\.cpp$||')

make -C build "$target"
"./build/$target"
