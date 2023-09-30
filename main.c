#include "library/library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc > 1) {
    if (strcmp(argv[1], "help") == 0) {
      printHelp();
      exit(0);
    }
  }
  system("clear");
  validateDatabse();
  autheticateUser();
  if (argc > 1) {
    if (strcmp(argv[1], "menu") == 0) {
      showMenu();
    } else if (strcmp(argv[1], "addnew") == 0) {
      addEntry();
    } else if (strcmp(argv[1], "all") == 0) {
      showStored();
    } else {
      printHelp();
    }
  } else {
    printHelp();
  }
  if (argc > 2) {
    if (strcmp(argv[1], "searchby") == 0) {
      if (!((strcmp(argv[2], "username") == 0) ||
            (strcmp(argv[2], "platform") == 0))) {
        printf("%s is not a searchby option.\n", argv[2]);
        printHelp();
        exit(1);
      }
      searchBy(argv[2]);
    }
  }
  return 0;
}
