#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> readlines(std::filesystem::path path, char sep) {
  std::ifstream stream(path);
  if (stream.bad()) {
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
};
Range splitHyphens(const std::string &line) {
  std::string sstart = line.substr(0, line.find('-'));
  std::string send = line.substr(sstart.length() + 1, line.length());
  int64_t start = std::stoll(sstart);
  int64_t end = std::stoll(send);
  return {start, end};
}
