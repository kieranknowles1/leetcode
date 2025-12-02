// https://adventofcode.com/2025/day/1

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

struct Dial {
  int position = 50;

  int submittedZeros = 0;
  int clickedZero = 0;

  void click(char direction) {
    position += (direction == 'R' ? 1 : -1);
    if (position < 0) {
      position += 100;
    } else if (position > 99) {
      position -= 100;
    }

    if (position == 0) {
      clickedZero++;
    }
  }
  void submit() {
    if (position == 0) {
      submittedZeros++;
    }
  }
};

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

struct Movement {
  char direction;
  int amount;

  Movement(std::string_view line) {
    this->direction = line[0];
    this->amount = std::stoi(line.data() + 1);
  }
};

Dial decodeFile(std::filesystem::path path) {
  auto lines = readlines(path);
  Dial dial;
  for (auto &line : lines) {
    Movement move(line);
    while (move.amount > 0) {
      dial.click(move.direction);
      move.amount--;
    }
    dial.submit();
  }

  return dial;
}

int main() {
  Dial ret = decodeFile("assets/1/example.txt");
  std::cout << "Got " << ret.submittedZeros << ", " << ret.clickedZero
            << ") expected 3, 6" << std::endl;

  Dial final = decodeFile("assets/1/input.txt");
  std::cout << "First answer: " << final.submittedZeros << ", "
            << final.clickedZero << std::endl;
}
