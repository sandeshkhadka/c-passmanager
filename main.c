#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library/library.h"

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
    }else if (strcmp(argv[1], "addnew") == 0) {
      addEntry(); 
    }
  }else {
    printf("At least one argument is needed.\nTry cpassmanager menu.\n");
  }
  if (argc > 2) {
    if (strcmp(argv[1], "searchby") == 0) {
      char searchby[10];
      printf("Enter %s: ",argv[2]);
      scanf("%s",searchby);
      char *sql = malloc(sizeof(char) * 60 * 50);
      memset(sql, 0, sizeof(char) * 60 * 50);
      // sql = sprintf(sql, "SELECT * FROM main WHERE %s IS %s",argv[1],searchby);
    }
  }
  return 0;
}
