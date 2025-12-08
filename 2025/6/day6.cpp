#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>

struct Column {
  char operation{};
  int width{};
  int pos{};
};

std::vector<Column> parse_operations(const std::string& line) {
  std::vector<Column> columns;

  int pos{};
  for (char c : line) {
    if (c != ' ') {
      if (!columns.empty())
        columns.back().width--;

      columns.emplace_back(c, 0, pos);
    }

    columns.back().width++;
    pos++;
  }

  return columns;
}

std::vector<std::string> parse_line_values(const std::string& line, const std::vector<Column>& columns) {
  std::vector<std::string> values;
  for (const auto& column : columns) {
    auto str = line.substr(column.pos, column.width);
    values.push_back(str);
  }

  return values;
}

std::vector<long long> column_values(int column_index, const std::vector<std::vector<std::string>>& matrix) {
  std::vector<long long> col_values;

  for (const auto& row_values : matrix)
    col_values.push_back(std::stoll(row_values[column_index]));

  return col_values;
}

std::vector<long long> cephalopod_column_values(int column_index, const std::vector<std::vector<std::string>>& matrix) {
  std::vector<long long> col_values;

  auto column_width = matrix[0][column_index].length();
  for (int i = 0; i < column_width; i++) {
    std::string value;
    for (const auto& row_values : matrix)
      value.push_back(row_values[column_index][i]);

    col_values.push_back(std::stoll(value));
  }

  return col_values;
}

long long do_operation(char operation, const std::vector<long long> values) {
  long long total{};
  
  for (long long value : values) {
    if (total == 0)
      total = value;
    else if (operation == '*')
      total *= value;
    else
      total += value;
  }

  return total;
}

long long sum_operations(const std::vector<Column>& columns, const std::vector<std::vector<std::string>>& matrix, auto col_function) {
  long long grand_total{};
  for (int i = 0; i < columns.size(); i++) {
    auto values = col_function(i, matrix);
    grand_total += do_operation(columns[i].operation, values);
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

    std::vector<Column> columns;

    std::string line;
    while(std::getline(fin, line))
      if (line.find_first_of("*+") != std::string::npos)
        columns = parse_operations(line);

    fin.clear();
    fin.seekg(0);

    std::vector<std::vector<std::string>> matrix;
    int line_number{};
    while(std::getline(fin, line)) {
      if (line.find_first_of("*+") == std::string::npos)
        matrix.push_back(parse_line_values(line, columns));
    }

    *out
      << "part 1: " << sum_operations(columns, matrix, &column_values) << std::endl
      << "part 2: " << sum_operations(columns, matrix, &cephalopod_column_values) << std::endl;

    return EXIT_SUCCESS;
 } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
