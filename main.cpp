#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

struct Utils {
  int length(char *argv[]) {
    int i = 0, total = 0;
    while (argv[1][i] != '\0') {
      i++, total++;
    }
    return total;
  }

  void press() {
    cout << "Press Enter to next...";
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    std::cin.get();
  }

  void clear_screen() { std::cout << "\033[2J\033[1;1H"; }
};

struct Error {
  void many_args(int &size) {
    if (size > 11)
      fprintf(stderr, "Too many argument\n");
  }

  void less_args(int &size) {
    if (size < 11)
      fprintf(stderr, "Student ID must be exactly 11 characters long\n");
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
      fprintf(stderr, "Student ID must be start with F1D02\n");
    }
  }

  int util_failed(Utils *util) {
    if (util == NULL) {
      fprintf(stderr, "failed to allocated memory\n");
      exit(1);
    }
    return 0;
  }

  int error_failed(Error *error) {
    if (error == NULL) {
      fprintf(stderr, "failed to allocated memory\n");
      exit(1);
    }
    return 0;
  }

  void input_failed(Utils *util) {
    fprintf(stderr, "Invalid input! Try again: \n");

    std::cin.clear();
    std::cin.ignore(1000, '\n');

    if (util != nullptr) {
      util->press();
      util->clear_screen();
    }
  }
};

int main(int argc, char *argv[]) {
  Utils *util;
  Error *error;

  error = (Error *)malloc(sizeof(*error));
  util = (Utils *)malloc(sizeof(*util));

  error->util_failed(util);

  int size = util->length(argv);

  error->many_args(size);
  error->less_args(size);
  error->not_prefix(argv);
  // free(error);
  // free(util);

  int option = -1;
  std::cout << R"(
    ============================================================
    SCHRYZA RESISTANCE, RECOVERY PROTOCOL [TERMINAL: PHOENIX]
    ============================================================
    You are CyroN's Memory Architect.
    Heed the gods and heal the sisters.
          )";
  util->press();
  util->clear_screen();

  do {
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
            )";
    std::cout << "Choose: ";
    std::cin >> option;

    if (std::cin.fail()) {
      error->input_failed(util);
      option = -1;
      continue;
    }

    switch (option) {
    case 1:
      cout << "halo";
      break;
    }

  } while (option != 0);

  return 0;
}
