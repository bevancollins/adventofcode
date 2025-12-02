#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <sstream>

bool is_part1_invalid_id(std::string& id) {
  // invalid ids have even length
  if (id.length() % 2 != 0)
    return false;

  auto first = id.substr(0, id.length() / 2);
  auto second = id.substr(id.length() / 2);

  return first == second;
}

bool is_part2_invalid_id(std::string& id) {
  for (int part_count = 2; part_count <= id.length(); part_count++) {
    if (id.length() % part_count == 0) {
      auto split_str = id.substr(0, id.length() / part_count);
      std::string combined_str;
      for (int i = 0; i < part_count; i++)
        combined_str += split_str;

      if (combined_str == id)
        return true;
    }
  }

  return false;
}

int main(int argc, char** argv) {
  assert(argc >= 2);

  try {
    std::ifstream fin;
    fin.exceptions(std::ifstream::badbit);
    fin.open(argv[1]);

    std::ostream* out = &std::cout;
    std::ofstream fout;
    if (argc == 3) {
      fout.exceptions(std::ifstream::badbit);
      fout.open(argv[2]);

      out = &fout;
    }

    long long part1_invalid_id_count{};
    long long part2_invalid_id_count{};

    std::string range;
    while (std::getline(fin, range, ',')) {
      auto pos = range.find('-');
      assert(pos != std::string::npos);

      auto from = std::stoll(range.substr(0, pos));
      auto to = std::stoll(range.substr(pos + 1));

      for (auto i = from; i <= to; i++) {
        auto id = std::to_string(i);
        if (is_part1_invalid_id(id))
          part1_invalid_id_count += i;

        if (is_part2_invalid_id(id))
          part2_invalid_id_count += i;
      }
    }

    *out << "part1: " << part1_invalid_id_count << std::endl;
    *out << "part2: " << part2_invalid_id_count << std::endl;

    return EXIT_SUCCESS;
 } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
