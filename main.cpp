#include <iostream>
#include <locale>
using namespace std;

struct Error {

  void many_args(int &size) {
    if (size > 11)
      cout << "Too many argument\n";
  }

  void less_args(int &size) {
    if (size < 11)
      cout << "Student ID must be exactly 11 characters long\n";
  }

  bool prefix(char *argv[]) {
    bool is_valid = true;
    char prefix[5] = {'F', '1', 'D', '0', '2'};
    int size = sizeof(prefix) / sizeof(prefix[0]);

    for (int i = 0; i < size; i++) {
      if (prefix[i] != argv[1][i]) {
        is_valid = false;
      }
    }

    return is_valid;
  }

  void not_prefix(char *argv[]) {
    if (!prefix(argv)) {
      cout << "Student ID must be F1D02\n";
    }
  }
};

int length(char *argv[]) {
  int i = 0, total = 0;
  while (argv[1][i] != '\0') {
    i++, total++;
  }
  return total;
}

bool valid(int &size, char *argv[]) {
  bool is_valid = true;
  return is_valid;
}

int main(int argc, char *argv[]) {

  int size = length(argv);

  Error error;
  error.many_args(size);
  error.less_args(size);
  error.not_prefix(argv);

  std::cout << R"(
  ------------------------------------------------------------
  Menu
  ------------------------------------------------------------
  1 - Show Historia's memories
  2 - Show Mira's memories
  3 - Show Victoria's memories
  4 - Add memory to a sister
  5 - Delete memory by index from a sister
  6 - Print sisters' pool diagnostics
  0 - Exit
  ------------------------------------------------------------
  Choose:
    )";

  return 0;
}
