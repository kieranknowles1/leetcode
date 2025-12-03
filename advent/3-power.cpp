#include <iostream>

#include "utils.hpp"

int charToInt(char c) { return c - '0'; }

int maxVoltage(std::string_view line) {
  int firstBattery = 0;
  int firstIdx = 0;

  for (int i = 0; i < line.length() - 1; i++) {
    int thisChar = charToInt(line[i]);
    if (thisChar > firstBattery) {
      firstBattery = thisChar;
      firstIdx = i;
    }
  }

  int secondBattery = 0;
  for (int i = firstIdx + 1; i < line.length(); i++) {
    int thisChar = charToInt(line[i]);
    if (thisChar > secondBattery) {
      secondBattery = thisChar;
    }
  }

  return (firstBattery * 10) + secondBattery;
}

int totalVoltage(std::filesystem::path file) {
  auto lines = readlines(file, '\n');
  int sum = 0;

  for (auto &line : lines) {
    int max = maxVoltage(line);
    std::cout << line << " " << max << std::endl;
    sum += max;
  }

  return sum;
}

int main() {
  int res = totalVoltage("assets/3/example.txt");
  std::cout << res << " expected 92" << std::endl;

  res = totalVoltage("assets/3/input.txt");
  std::cout << "Total: " << res << std::endl;
}
