#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <sstream>

bool is_invalid_id(auto id) {
  auto id_str = std::to_string(id);

  // invalid ids have even length
  if (id_str.length() % 2 != 0)
    return false;

  auto first = id_str.substr(0, id_str.length() / 2);
  auto second = id_str.substr(id_str.length() / 2);

  return first == second;
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

    long long invalid_id_count{};

    std::string range;
    while (std::getline(fin, range, ',')) {
      auto pos = range.find('-');
      assert(pos != std::string::npos);

      auto from_str = range.substr(0, pos);
      auto to_str = range.substr(pos + 1);

      auto from = std::stoll(from_str);
      auto to = std::stoll(to_str);

      for (auto i = from; i <= to; i++)
        if (is_invalid_id(i))
          invalid_id_count += i;
    }

    *out << invalid_id_count << std::endl;

    return EXIT_SUCCESS;
 } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
