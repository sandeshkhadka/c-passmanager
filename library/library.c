#include "library.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct entry {
  char platform[20];
  char username[20];
  char password[20];
};

void help() {}

void cib() {
  while (getchar() != '\n')
    ; // clear the input buffer
}
void showMenu() {
  int choice;
  printf("\n1. Add new password\n2. Edit existing password\n3. Show stored "
         "password\n");
  printf("Choice(1-3): ");
  scanf("%d", &choice);
  switch (choice) {
  case 1:
    cib();
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
  newEntry.platform[strcspn(newEntry.platform, "\n")] = 0;
  printf("Username: ");
  fgets(newEntry.username, 20, stdin);
  newEntry.username[strcspn(newEntry.username, "\n")] = 0;
  printf("Password: ");
  fgets(newEntry.password, 20, stdin);
  newEntry.password[strcspn(newEntry.password, "\n")] = 0;
  char *sql =
      malloc(sizeof(char) * strlen(newEntry.password) *
             strlen(newEntry.username) * strlen(newEntry.platform) * 50);
  memset(sql, 0,
         sizeof(char) * strlen(newEntry.password) * strlen(newEntry.username) *
             strlen(newEntry.platform) * 50);
  sprintf(sql, "INSERT INTO main VALUES('%s','%s','%s')", newEntry.platform,
          newEntry.username, newEntry.password);
  sqlExecute(sql, NULL);
}


void editEntry() {}


void showStored() {
  char *sql = "SELECT * FROM main";
  sqlExecute(sql, printCallback);
}


void sqlExecute(char *sql, int (*callback)(void *, int, char **, char **)){
  sqlite3 *db;
  char *err_msg;
  int rc = sqlite3_open("passwords.db", &db);
  if (rc != SQLITE_OK) {
    printf("Connection to db failed.\nError: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(1);
  }
  rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
  if (rc!=SQLITE_OK) {
    printf("Error: %s",err_msg);
    sqlite3_free(err_msg);
    sqlite3_close(db);
  }
}

void validateDatabse() {
  char *sql = "CREATE TABLE IF NOT EXISTS main(platform TEXT, username TEXT, "
              "password TEXT)";
  sqlExecute(sql, NULL);
}


int printCallback(void *data, int argc, char **argv, char **azColName) {
  int i;
  for (i = 0; i < argc; i++) {
    printf("%s : %s | ", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}
