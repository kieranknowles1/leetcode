#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
#include <vector>

#include "utils.hpp"

constexpr char Source = 'S';
constexpr char Splitter = '^';
constexpr char Beam = '|';
constexpr char Empty = '.';

using NetworkId = int;

struct Junction {
  Vector3 position;
  NetworkId id;
  NetworkId network;
};

struct Connection {
  NetworkId from;
  NetworkId to;
};

struct Candidate {
  Junction *a;
  Junction *b;
  int64_t distance;
};

struct Solver {
  std::vector<Junction> junctions;
  std::vector<Connection> connections;

  Solver(const std::vector<std::string> &lines) {
    for (int i = 0; i < lines.size(); i++) {
      Vector3 point(lines[i]);
      junctions.emplace_back(point, i, i);
    }
  }

  bool connected(Junction a, Junction b) {
    for (auto &conn : connections) {
      if ((conn.from == a.id && conn.to == b.id) ||
          (conn.from == b.id && conn.to == a.id))
        return true;
    }
    return false;
  }

  void connect(Junction &a, Junction &b, int64_t distance) {
    std::cout << "Connect " << a.position << " and " << b.position << " dist "
              << distance << std::endl;
    int newNet = std::min(a.network, b.network);
    std::cout << "Merge " << a.network << " and " << b.network << " -> "
              << newNet << std::endl;
    connections.emplace_back(a.id, b.id);

    for (auto &j : junctions) {
      if (j.network == a.network || j.network == b.network) {
        j.network = newNet;
      }
    }
  }

  void joinClosest(int n) {
    std::vector<Candidate> candidates;
    for (int a = 0; a < junctions.size(); a++) {
      for (int b = a + 1; b < junctions.size(); b++) {
        auto &ja = junctions[a];
        auto &jb = junctions[b];
        candidates.emplace_back(&ja, &jb,
                                ja.position.distanceSquared(jb.position));
      }
    }
    std::sort(candidates.begin(), candidates.end(),
              [](auto &a, auto &b) { return a.distance < b.distance; });

    for (int i = 0; i < n; i++) {
      connect(*candidates[i].a, *candidates[i].b, candidates[i].distance);
    }

    // int bestA = -1;
    // int bestB = -1;
    // int64_t bestDistance = std::numeric_limits<int>::max();

    // for (int a = 0; a < junctions.size(); a++) {
    //   for (int b = a + 1; b < junctions.size(); b++) {
    //     auto &ja = junctions[a];
    //     auto &jb = junctions[b];
    //     // Already connected
    //     if (connected(ja, jb))
    //       continue;
    //     // if (ja.network == jb.network)
    //     //   continue;

    //     auto dist = ja.position.distanceSquared(jb.position);
    //     if (dist < bestDistance) {
    //       bestA = a;
    //       bestB = b;
    //       bestDistance = dist;
    //     }
    //   }
    // }

    // auto &ja = junctions[bestA];
    // auto &jb = junctions[bestB];
    // connect(ja, jb);
  }

  std::vector<std::pair<NetworkId, int>> largestNetworks(int count) {
    std::map<NetworkId, int> counts;
    for (auto &j : junctions) {
      counts[j.network] = counts[j.network] + 1;
    }

    std::vector<std::pair<NetworkId, int>> vec(counts.begin(), counts.end());
    std::sort(vec.begin(), vec.end(),
              [](auto &a, auto &b) { return a.second > b.second; });
    vec.resize(count);
    return vec;
  }
};

uint64_t cicruitSizes(std::filesystem::path file, int cables) {
  auto lines = readlines(file, '\n');
  Solver solver(lines);

  solver.joinClosest(cables);

  int64_t mult = 1;
  auto sizes = solver.largestNetworks(3);
  for (auto size : sizes) {
    mult *= size.second;
    std::cout << "Network of " << size.second << std::endl;
  }
  return mult;
}

int main() {
  uint64_t res = cicruitSizes("assets/8/example.txt", 10);
  std::cout << res << " expected 40" << std::endl;

  res = cicruitSizes("assets/8/input.txt", 1000);
  std::cout << "Total: " << res << std::endl;
}
