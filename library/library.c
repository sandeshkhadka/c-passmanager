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
         "password\n4.Delete password\n");
  printf("Choice(1-4): ");
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
  case 4:
    deleteEntry();
    break;
  }
}

void addEntry() {
  system("clear");
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
  sprintf(sql, "INSERT INTO main (platform,username,password) VALUES('%s','%s','%s')", newEntry.platform,
          newEntry.username, newEntry.password);
  sqlExecute(sql, NULL);
}

void searchBy(char *searchField){
      system("clear");
      char searchChoice[20];
      printf("Enter %s: ", searchField);
      fgets(searchChoice, 20, stdin);
      searchChoice[strcspn(searchChoice, "\n")] = 0;
      char *sql = malloc(sizeof(char) * 60 * 50);
      memset(sql, 0, sizeof(char) * 60 * 50);
      sprintf(sql, "SELECT * FROM main WHERE %s='%s'", searchField, searchChoice);
      system("clear");
      printAllFields();
      sqlExecute(sql, printCallback);
}
int findId(){
  int choice;
  printf("1. Search by platform\n2. Search by username\n3. Search by password\n");
  printf("Choice(1-3): ");
  scanf("%d", &choice);
  cib();
  system("clear");
  switch (choice) {
  case 1:
    searchBy("platform");
    break;
  case 2:
    searchBy("username");
    break;
  case 3:
    searchBy("password");
    break;
  }
  printf("Enter id : ");
  int id;
  scanf("%d", &id);
  cib();
  return id; 
}
void editEntry() {
  system("clear");
  int id = findId();
  int choice;
  printf("1. Edit platform\n2. Edit username\n3. Edit password\n");
  printf("Choice(1-3): ");
  scanf("%d", &choice);
  cib();
  system("clear");
  char *field;
  switch (choice) {
  case 1:
    field = "platform";
    break;
  case 2:
    field = "username";
    break;
  case 3:
    field = "password";
    break;
  }
  char newValue[20];
  printf("Enter new %s: ", field);
  fgets(newValue, 20, stdin);
  newValue[strcspn(newValue, "\n")] = 0;
  char *sql = malloc(sizeof(char) * 60 * 50);
  memset(sql, 0, sizeof(char) * 60 * 50);
  sprintf(sql, "UPDATE main SET %s='%s' WHERE id=%d", field, newValue, id);
  sqlExecute(sql, NULL);
}
void deleteEntry() {
  system("clear");
  int id = findId();
  char *sql = malloc(sizeof(char) * 60 * 50);
  memset(sql, 0, sizeof(char) * 60 * 50);
  sprintf(sql, "DELETE FROM main WHERE id=%d", id);
  sqlExecute(sql, NULL);
}

void showStored() {
  system("clear");
  char *sql = "SELECT * FROM main";
  printAllFields();
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
  char *sql = "CREATE TABLE IF NOT EXISTS main ("
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "password TEXT,"
    "username TEXT,"
    "platform TEXT)";
    sqlExecute(sql, NULL);
}


int printCallback(void *data, int argc, char **argv, char **azColName) {
  int i;
  for (i = 0; i < argc; i++) {
    printf("|\t");
    printf("%s ", argv[i] ? argv[i] : "NULL");
    printf("\t|");
  }
  printf("\n");
  return 0;
}
int printFieldsCallback(void *data, int argc, char **argv, char **azColName) {
  printf("|\t");
  printf("%s ", argv[1] ? argv[1] : "NULL");
  printf("\t|");
  return 0;
}
void printAllFields(){
  char *sql = "PRAGMA table_info(main)";
  sqlExecute(sql, printFieldsCallback);
  printf("\n");
}
