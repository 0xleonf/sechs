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

  int str_len(const char *string) {
    int i = 0, total = 0;
    while (string[i] != '\0') {
      i++, total++;
    }
    return total;
  }

  void strcopy(char *destination, const char *source) {
    int i = 0;
    while (source[i] != '\0') {
      destination[i] = source[i];
      i++;
    }
    destination[i] = '\0';
  }

  bool is_prime(int n) {
    if (n <= 1)
      return false;

    for (int i = 2; i * i <= n; i++) {
      if (n % i == 0)
        return false;
    }

    return true;
  }

  int generate_next_prime(int curr_prime) {
    int number = curr_prime + 1;

    while (is_prime(number)) {
      number++;
    }

    return number;
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

  void check_allocation(void *ptr) {
    if (ptr == NULL) {
      fprintf(stderr, "Error: Failed to allocate memory\n");
      exit(1);
    }
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

struct Memory {
  char type[3][10];
  int type_index;
  size_t offset;
  size_t size;
  size_t jump;
  char value[511];
};

struct Sister {
  // char name[10];
  size_t pool_size;
  size_t alignment;
  size_t curr_offset;
  int special_gap;
  int curr_prime;
  int bump;

  Memory memories[50];
  int memory_count = 0;

  void new_bump(int size) {
    int new_bump = this->curr_offset + size;
    this->bump = new_bump;
  }

  int align_up(uint old_bump, int alignment) {
    if (old_bump == 0)
      return 0;

    else
      return ((old_bump / alignment) + 1) * alignment;
  }

  void init() {
    Utils *util;

    util = (Utils *)malloc(sizeof(*util));

    for (int i = 0; i < 50; i++) {
      util->strcopy(this->memories[i].type[0], "char*");
      util->strcopy(this->memories[i].type[1], "uint");
      util->strcopy(this->memories[i].type[2], "double");
    }
    this->bump = 0;
  }

  int historia(char *argv[]) {
    int number;
    if ((int)argv[1][10] % 2 != 0) {
      number = 1;
    } else {
      number = 0;
    }
    return number;
  }

  // converts 3 digit from char to int (dynamic allocation)
  int victoria(char *argv[]) {
    // base ascii 0
    int base = 48;
    int last_digit[3] = {(int)argv[1][8], (int)argv[1][9], (int)argv[1][10]};

    int size = sizeof(last_digit) / sizeof(last_digit[0]);
    int *arr = (int *)malloc(size * sizeof(int));

    if (arr != NULL) {
      for (int i = 0; i < size; i++) {
        arr[i] = (last_digit[i] - base);
      }
    }

    int sum = ((arr[0] * 100) + (arr[1] * 10) + (arr[2]) * 1);

    free(arr);
    return (sum * 11 % 53) + 14;
  }

  int mira(char *argv[]) {
    int base = 48;
    int last_digit[3] = {(int)argv[1][8], (int)argv[1][9], (int)argv[1][10]};

    int size = sizeof(last_digit) / sizeof(last_digit[0]);
    int *arr = (int *)malloc(size * sizeof(int));

    if (arr != NULL) {
      for (int i = 0; i < size; i++) {
        arr[i] = (last_digit[i] - base);
      }
    }

    int sum = ((arr[0] * 100) + (arr[1] * 10) + (arr[2]) * 1);

    free(arr);

    return (sum * 7 % 23) + 12;
  }

  void add_memory(const char *type, const char *value, const char *sister,
                  char *argv[]) {

    Utils *util;

    util = (Utils *)malloc(sizeof(*util));
    int size_data = 0;

    int special_gap, aligned;
    int old_bump = this->bump;
    // checking historia
    if (sister[0] == 'H') {
      this->pool_size = 1024;
      special_gap = historia(argv);
      this->special_gap = special_gap;
      aligned = this->align_up(this->bump, 16);
      this->alignment = 16;
    }
    // checking mira
    else if (sister[0] == 'M') {
      this->pool_size = 2048;
      special_gap = mira(argv);
      this->special_gap = special_gap;
      aligned = this->align_up(this->bump, 8);
      this->alignment = 8;
    }
    // checking victoria
    else if (sister[0] == 'V') {
      this->pool_size = 4096;
      special_gap = victoria(argv);
      this->special_gap = special_gap;
      aligned = this->align_up(this->bump, 4);
      this->alignment = 4;
    }

    if (type[0] == 'c') {

      cout << "0 -> char*\n";
      int len = util->str_len(value);
      size_data = len + 1;

      this->memory_count++;

      int final_offset = aligned + special_gap;
      this->curr_offset = final_offset;
      // this->alignment = aligned;
      this->new_bump(size_data);

      int idx = this->memory_count - 1;
      this->memories[idx].type_index = 0;
      this->memories[idx].size = size_data;
      this->memories[idx].offset = this->curr_offset;
      this->memories[idx].jump = this->curr_offset - old_bump;
      util->strcopy(this->memories[idx].value, value);

    } else if (type[0] == 'u') {
      cout << "1 -> uint\n";
      size_data = 4;

      this->memory_count++;

      int final_offset = aligned + special_gap;
      this->curr_offset = final_offset;
      // this->alignment = aligned;
      this->new_bump(size_data);

      int idx = this->memory_count - 1;
      this->memories[idx].type_index = 1;
      this->memories[idx].size = size_data;
      this->memories[idx].offset = this->curr_offset;
      this->memories[idx].jump = this->curr_offset - old_bump;
      util->strcopy(this->memories[idx].value, value);

    } else {
      cout << "2 -> double\n";
      size_data = 8;
      this->memory_count++;

      int final_offset = aligned + special_gap;
      this->curr_offset = final_offset;
      // this->alignment = aligned;
      this->new_bump(size_data);

      int idx = this->memory_count - 1;
      this->memories[idx].type_index = 2;
      this->memories[idx].size = size_data;
      this->memories[idx].offset = this->curr_offset;
      this->memories[idx].jump = this->curr_offset - old_bump;
      util->strcopy(this->memories[idx].value, value);
    }

    free(util);
  }

  // void display_sister(const char *string) {
  //   int count = 1;
  //
  //   cout << "
  //   ------------------------------------------------------------\n";
  //   std::cout << "Memory from: " << string << "\n";
  //   cout << "
  //   ------------------------------------------------------------\n"; cout <<
  //   "[0] Type: " << this->memories->type[this->memory_count];
  // }

  void display_sister(const char *string) {
    cout << "------------------------------------------------------------\n";
    cout << "Memories of " << string << "\n";
    cout << "------------------------------------------------------------\n";

    for (int i = 0; i < this->memory_count; i++) {
      int t = this->memories[i].type_index;
      cout << "[" << i << "] Type: " << this->memories[i].type[t];
      cout << " | Size: " << this->memories[i].size;
      cout << " | Offset: " << this->memories[i].offset;
      cout << " | Address: " << (void *)this->memories[i].value;
      cout << " | Value: " << this->memories[i].value << "\n";
    }

    cout << "Bump: " << this->bump;
    cout << " | Pool Size: " << this->pool_size;
    cout << " | Align: " << this->alignment;
    cout << " | Special Gap: +" << this->special_gap << "\n";
  }
};

int main(int argc, char *argv[]) {
  Utils *util;
  Error *error;
  Memory *memory;
  Sister *historia, *mira, *victoria;

  error = (Error *)malloc(sizeof(*error));
  util = (Utils *)malloc(sizeof(*util));
  memory = (Memory *)malloc(sizeof(*memory));
  historia = (Sister *)malloc(sizeof(*historia));
  mira = (Sister *)malloc(sizeof(*mira));
  mira = (Sister *)malloc(sizeof(*mira));

  error->check_allocation(util);

  int size = util->length(argv);

  error->many_args(size);
  error->less_args(size);
  error->not_prefix(argv);

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

  historia->init();
  cout << historia->bump;
  historia->add_memory("char*", "Halo", "Historia", argv);
  // historia->add_memory("char*", "Halo", "Historia", argv);
  historia->add_memory("uint", "33", "Historia", argv);
  historia->display_sister("Historia");
  cout << "\n";

  // cout << historia[0].memories[0]

  // cout << historia->memory_count;
  // util->strcopy(historia[0].name, "Historia");
  // cout << historia[0].name;
  // cout << "Historia: " << historia->historia(argv) << "\n"
  //      << "Mira: " << mira->mira(argv) << "\n"
  //      << "victoria: " << victoria->victoria(argv) << "\n";

  // do {
  //   std::cout << R"(
  //   ------------------------------------------------------------
  //     Menu
  //   ------------------------------------------------------------
  //       1 - Show Historia's memories
  //       2 - Show Mira's memories
  //       3 - Show Victoria's memories
  //       4 - Add memory to a sister
  //       5 - Delete memory by index from a sister
  //       6 - Print sisters' pool diagnostics
  //       0 - Exit
  //   ------------------------------------------------------------
  //           )";
  //   std::cout << "Choose: ";
  //   std::cin >> option;
  //
  //   if (std::cin.fail()) {
  //     error->input_failed(util);
  //     option = -1;
  //     continue;
  //   }
  //
  //   switch (option) {
  //   case 1:
  //     char type[3][20];
  //     util->strcopy(historia[0].name, "Historia");
  //     historia->memories->size = 32;
  //     historia->pool_size = 1024;
  //   }
  //
  // } while (option != 0);

  // free all memories after exit
  free(error), free(util), free(historia), free(mira), free(victoria);

  return 0;
}
