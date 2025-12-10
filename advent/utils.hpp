#pragma once

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> readlines(std::filesystem::path path, char sep) {
  std::ifstream stream(path);
  if (!stream.is_open()) {
    throw std::runtime_error("Unable to read file");
  }

  std::vector<std::string> out;
  for (std::string line; std::getline(stream, line, sep);) {
    out.push_back(line);
  }
  return out;
}

struct Range {
  int64_t begin;
  int64_t end;

  void print() { std::cout << begin << '-' << end << std::endl; }
};

bool operator<(const Range &lhs, const Range &rhs) {
  return lhs.begin < rhs.begin;
}

struct Vector2 {
  int x;
  int y;
};
bool operator<(const Vector2 &lhs, const Vector2 &rhs) {
  if (lhs.x < rhs.x)
    return true;
  if (lhs.x > rhs.x)
    return false;
  return lhs.y < rhs.y;
}
bool operator==(const Vector2 &lhs, const Vector2 &rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

Range splitHyphens(const std::string &line) {
  std::string sstart = line.substr(0, line.find('-'));
  std::string send = line.substr(sstart.length() + 1, line.length());
  int64_t start = std::stoll(sstart);
  int64_t end = std::stoll(send);
  return {start, end};
}
