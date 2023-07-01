#include "library/library.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct entry {
  char platform[20];
  char username[20];
  char password[20];
};

int main(int argc, char *argv[]) {
  validateDatabse();
  if (argc > 1) {
    if (strcmp(argv[1], "menu") == 0) {
      showMenu();
    } else if (strcmp(argv[1], "addnew") == 0) {
      addEntry();
    }
  } else {
    printf("At least one argument is needed.\nTry cpassmanager menu.\n");
  }
  if (argc > 2) {
    if (strcmp(argv[1], "searchby") == 0) {
      if (!((strcmp(argv[2], "username") == 0) ||
            (strcmp(argv[2], "password") == 0) ||
            (strcmp(argv[2], "platform") == 0))) {
        printf("%s is not a searchby option.\n", argv[2]);
        exit(1);
      }
      searchBy(argv[2]);
          }
  }
  return 0;
}
