#include <stdio.h>
#include <string.h>
void addEntry();
void showMenu();
void editEntry();
void showStored();
void cib() {
  while (getchar() != '\n')
    ; // clear the input buffer
}
struct entry {
  char platform[20];
  char username[20];
  char password[20];
};

int main(int argc, char *argv[]) {
  if (argc > 1) {
    if (strcmp(argv[1], "menu") == 0) {
      showMenu();
    }
  }
  return 0;
}

void showMenu() {
  int choice;
  printf("\n1. Add new password\n2. Edit existing password\n3. Show stored "
         "password\n");
  printf("Choice(1-3): ");
  scanf("%d", &choice);
  cib();
  switch (choice) {
  case 1:
    addEntry();
    break;
  case 2:
    editEntry();
    break;
  case 3:
    showStored();
    break;
  }
}

void addEntry() {
  struct entry newEntry;
  printf("Platform: ");
  fgets(newEntry.platform, 20, stdin);
  printf("Username: ");
  fgets(newEntry.username, 20, stdin);
  printf("Password: ");
  fgets(newEntry.password, 20, stdin);
}
void editEntry() {}
void showStored() {}
