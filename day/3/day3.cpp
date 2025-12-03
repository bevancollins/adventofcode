#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <string_view>
#include <algorithm>
#include <utility>

int largest_joltage(std::string_view batteries) {
  if (batteries.length() < 2)
    return 0;

  char digits[3]{
    batteries[0],
    batteries[1],
    '\0'
  };
  for (size_t i = 2; i < batteries.length(); i++)
    digits[1] = std::max(digits[1], batteries[i]);

  auto joltage = std::stoi(digits);

  return std::max(joltage, largest_joltage(batteries.substr(1)));
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

    long long total{};
    std::string line;
    while(std::getline(fin, line)) {
      auto joltage = largest_joltage(line);
      *out << joltage << std::endl;

      total += joltage;
    }

    std::cout << "part1: " << total << std::endl;

    return EXIT_SUCCESS;
 } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
