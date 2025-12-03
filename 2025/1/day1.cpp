#include <iostream>
#include <fstream>
#include <cassert>

constexpr int dial_mod{100};

struct state {
  int dial{50};
  int dial_zero_count{};
  int click_zero_count{};

  void rotate(int rotation) {
    if (rotation > 0) {
      click_zero_count += (dial + rotation) / dial_mod;
    } else {
      click_zero_count -= rotation / dial_mod;
      if (dial > 0 && dial + (rotation % dial_mod) < 0)
        click_zero_count++;
    }

    dial += rotation;

    dial %= dial_mod;
    if (dial < 0)
      dial += dial_mod;

    if (dial == 0) {
      dial_zero_count++;

      if (rotation < 0)
        click_zero_count++;
    }
  }
};

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

    state state;
    char dir;
    int rotation;
    while (fin >> dir >> rotation) {
      *out << dir << rotation << " ";

      if (dir == 'L')
        rotation = -1 * rotation;

      state.rotate(rotation);

      *out << "D" << state.dial << " DZ" << state.dial_zero_count << " CZ" << state.click_zero_count << std::endl;
    }

    std::cout
      << "password: " << state.dial_zero_count << std::endl
      << "method 0x434C49434B: " << state.click_zero_count << std::endl;
    return EXIT_SUCCESS;
 } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
