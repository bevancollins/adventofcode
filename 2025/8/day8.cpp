#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>

struct JunctionBox;

struct DistanceBetween {
  double distance{};
  std::pair<JunctionBox*, JunctionBox*> junction_boxes;

  bool operator < (const DistanceBetween& other) const {
    return distance < other.distance;
  }
};

struct Coordinate {
  int x{};
  int y{};
  int z{};

  auto distance_to(const Coordinate& other) const {
    return std::sqrt(
        std::pow(x - other.x, 2) +
        std::pow(y - other.y, 2) +
        std::pow(z - other.z, 2));
  }
};

struct JunctionBox {
  Coordinate location;
};

struct Circuit {
  std::set<JunctionBox*> juction_boxes;

  bool operator < (const Circuit& other) const {
    return juction_boxes.size() < other.juction_boxes.size();
  }
};

std::vector<JunctionBox*> read_input(std::istream& fin) {
  std::vector<JunctionBox*> junction_boxes;

  std::string x, y, z;
  while (std::getline(fin, x, ',') && std::getline(fin, y, ',') && std::getline(fin, z)) {
    auto jb = new JunctionBox();
    jb->location = { std::stoi(x), std::stoi(y), std::stoi(z) };

    junction_boxes.push_back(jb);
  }

  return junction_boxes;
}

std::vector<DistanceBetween> calculate_distances(const std::vector<JunctionBox*> junction_boxes) {
  std::vector<DistanceBetween> distances;

  for (int i = 0; i < junction_boxes.size(); i++) {
    for (int j = i + 1; j < junction_boxes.size(); j++) {
      auto d = junction_boxes[i]->location.distance_to(junction_boxes[j]->location);
      distances.emplace_back(d, std::make_pair(junction_boxes[i], junction_boxes[j]));
    }
  }

  return distances;
}

auto find_circuit(std::vector<Circuit>& circuits, JunctionBox* jb) {
  auto it = circuits.begin();
  for (; it != circuits.end(); it++)
    if (it->juction_boxes.contains(jb))
      break;

  return it;
}

std::vector<Circuit> make_connections(const std::vector<JunctionBox*> junction_boxes, int connection_count) {
  // initially all junction boxes belong to their own circuit
  std::vector<Circuit> circuits;
  for (const auto& jb : junction_boxes) {
    std::set<JunctionBox*> s{jb};
    circuits.emplace_back(s);
  }

  auto distances = calculate_distances(junction_boxes);
  std::sort(distances.rbegin(), distances.rend());  // sort distances descending

  for (int i = 0; i < connection_count && !distances.empty(); i++) {
    const auto shortest_distance = distances.back();

    // find the circuits the junction boxes are attached to
    auto first_circuit = find_circuit(circuits, shortest_distance.junction_boxes.first);
    assert(first_circuit != circuits.end());

    auto second_circuit = find_circuit(circuits, shortest_distance.junction_boxes.second);
    assert(second_circuit != circuits.end());

    if (first_circuit != second_circuit) {
      // merge the circuits
      first_circuit->juction_boxes.merge(second_circuit->juction_boxes);
      circuits.erase(second_circuit);
    }

    distances.pop_back();
  }

  return circuits;
}

int main(int argc, char** argv) {
  assert(argc >= 3);

  try {
    std::ifstream fin;
    fin.exceptions(std::ifstream::badbit);
    fin.open(argv[2]);

    std::ostream* out = &std::cout;
    std::ofstream fout;
    if (argc == 4) {
      fout.exceptions(std::ifstream::badbit);
      fout.open(argv[3]);

      out = &fout;
    }

    auto connection_count = std::stoi(argv[1]);

    auto junction_boxes = read_input(fin);
    auto circuits = make_connections(junction_boxes, connection_count);
    std::sort(circuits.rbegin(), circuits.rend());

    assert(circuits.size() >= 3);
    auto total =
      circuits[0].juction_boxes.size() *
      circuits[1].juction_boxes.size() *
      circuits[2].juction_boxes.size();

    *out
      << total << std::endl;

    return EXIT_SUCCESS;
 } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
