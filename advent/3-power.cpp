#include <cmath>
#include <cstdint>
#include <iostream>

#include "utils.hpp"

const constexpr int ActiveBatteries = 12;

int charToInt(char c) { return c - '0'; }

uint64_t ipow(uint64_t base, uint64_t exp) {
  uint64_t result = 1;
  for (int i = 0; i < exp; i++) {
    result *= base;
  }
  return result;
}

uint64_t maxVoltage(std::string_view line, int active) {
  uint64_t firstBattery = 0;
  int firstIdx = 0;

  for (int i = 0; i <= line.length() - active; i++) {
    int thisChar = charToInt(line[i]);
    if (thisChar > firstBattery) {
      firstBattery = thisChar;
      firstIdx = i;
    }
  }

  uint64_t totalPower = firstBattery * ipow(10, active - 1);
  if (active > 1) {
    totalPower += maxVoltage(line.substr(firstIdx + 1), active - 1);
  }
  return totalPower;
}

uint64_t totalVoltage(std::filesystem::path file) {
  auto lines = readlines(file, '\n');
  uint64_t sum = 0;

  for (auto &line : lines) {
    uint64_t max = maxVoltage(line, ActiveBatteries);
    sum += max;
  }

  return sum;
}

int main() {
  uint64_t res = totalVoltage("assets/3/example.txt");
  std::cout << res << " expected 3121910778619" << std::endl;

  res = totalVoltage("assets/3/input.txt");
  std::cout << "Total: " << res << std::endl;
}
