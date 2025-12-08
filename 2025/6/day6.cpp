#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include <sstream>

std::string parse_operations(const std::string& line) {
  std::string operations(line);
  std::erase(operations, ' ');

  return operations;
}

std::vector<int> parse_numbers(const std::string& line) {
  std::vector<int> numbers;
  std::stringstream ss(line);
  while (!ss.eof()) {
    int number{};
    ss >> number;
    if (number == 0 && ss.fail())
      break;
    numbers.push_back(number);
  }

  return numbers;
}

long long sum_operations(const std::vector<std::vector<int>>& matrix, const std::string& operations) {
  long long grand_total{};

  for (int i = 0; i < operations.size(); i++) {
    bool first_operation = true;
    long long total{};
    for (const auto& numbers : matrix) {
      assert(numbers.size() > i);

      assert(operations[i] == '*' || operations[i] == '+');
      if (first_operation) {
        first_operation = false;
        total = numbers[i];
      } else {
        if (operations[i] == '*')
          total *= numbers[i];
        else
          total += numbers[i];
      }
    }
    grand_total += total;
  }

  return grand_total;
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

    std::vector<std::vector<int>> numbers;
    std::string operations;
    std::string line;
    while(std::getline(fin, line)) {
      if (line.find_first_of("+*") != std::string::npos) {
        operations = parse_operations(line);
        break;
      } else {
        numbers.push_back(parse_numbers(line));
      }
    }

    auto total = sum_operations(numbers, operations);

    *out << total << std::endl;

    return EXIT_SUCCESS;
 } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
