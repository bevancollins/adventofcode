#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

long long largest_joltage(const std::string& batteries, int battery_count) {
  assert(batteries.length() >= battery_count);

  std::string joltage;

  int pos{};
  for (int i = 0; i < battery_count; i++) {
    int highest_pos{pos};
    for (int j = pos + 1; j <= batteries.length() - (battery_count - i); j++) {
      if (batteries[j] > batteries[highest_pos])
        highest_pos = j;
    }
    pos = highest_pos + 1;
    joltage += batteries[highest_pos];
  }

  return std::stoll(joltage);
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

    long long totals[2]{};
    std::string line;
    while(std::getline(fin, line)) {
      totals[0] += largest_joltage(line, 2);
      totals[1] += largest_joltage(line, 12);
    }

    *out << "part1: " << totals[0] << std::endl;
    *out << "part2: " << totals[1] << std::endl;

    return EXIT_SUCCESS;
 } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
