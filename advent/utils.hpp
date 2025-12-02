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
