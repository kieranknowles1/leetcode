// https://adventofcode.com/2025/day/1

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<std::string> readlines(std::filesystem::path path) {
  std::ifstream stream(path);
  if (stream.bad()) {
    throw std::runtime_error("Unable to read file");
  }

  std::vector<std::string> out;
  for (std::string line; std::getline(stream, line);) {
    out.push_back(line);
  }
  return out;
}

int parseMovement(std::string_view line) {
  char direction = line[0];
  int amount = std::stoi(line.data() + 1);
  return amount * (direction == 'R' ? 1 : -1);
}

int decodeFile(std::filesystem::path path) {
  auto lines = readlines(path);
  int position = 50;
  int zeros = 0;
  for (auto &line : lines) {
    int amount = parseMovement(line);
    position += amount;

    if (position % 100 == 0)
      zeros++;
  }

  return zeros;
}

int main() {
  int ret = decodeFile("assets/1/example.txt");
  std::cout << "Got " << ret << " expected 3" << std::endl;

  int final = decodeFile("assets/1/input.txt");
  std::cout << "First answer: " << final << std::endl;
}
