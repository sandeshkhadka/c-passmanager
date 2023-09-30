#include "library.h"
#include "encrypt_decrypt.h"
#include <sodium.h>
#include <sodium/crypto_pwhash.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct entry {
  char platform[MAX_PAINTEXT_LEN];
  char username[MAX_PAINTEXT_LEN];
  char password[MAX_PAINTEXT_LEN];
};
unsigned char key[crypto_secretbox_KEYBYTES] = "mysecretkey";
unsigned char nonce[crypto_secretbox_NONCEBYTES] = "mysecretnonce";
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
  fgets(newEntry.platform, MAX_PAINTEXT_LEN, stdin);
  newEntry.platform[strcspn(newEntry.platform, "\n")] = 0;
  printf("Username: ");
  fgets(newEntry.username, MAX_PAINTEXT_LEN, stdin);
  newEntry.username[strcspn(newEntry.username, "\n")] = 0;
  printf("Password: ");
  fgets(newEntry.password, MAX_PAINTEXT_LEN, stdin);
  newEntry.password[strcspn(newEntry.password, "\n")] = 0;
  size_t password_len = strlen(newEntry.password);
  char *hashed_password = encrypt(newEntry.password, key, nonce);
  char *sql =
      malloc(sizeof(char) * strlen(hashed_password) *
             strlen(newEntry.username) * strlen(newEntry.platform) * 50);
  memset(sql, 0,
         sizeof(char) * strlen(hashed_password) * strlen(newEntry.username) *
             strlen(newEntry.platform) * 50);
  sprintf(sql,
          "INSERT INTO main (platform,username,password,l) "
          "VALUES('%s','%s','%s','%ld')",
          newEntry.platform, newEntry.username, hashed_password, password_len);
  sqlExecute(sql, NULL, NULL, NULL);
}

void searchBy(char *searchField) {
  system("clear");
  char searchChoice[20];
  printf("Enter %s: ", searchField);
  fgets(searchChoice, 20, stdin);
  searchChoice[strcspn(searchChoice, "\n")] = 0;
  char *sql = malloc(sizeof(char) * 60 * 50);
  memset(sql, 0, sizeof(char) * 60 * 50);
  sprintf(sql, "SELECT * FROM main WHERE %s='%s'", searchField, searchChoice);
  system("clear");
  // printAllFields();
  sqlExecute(sql, printAllPasswords, NULL, NULL);
}
int findId() {
  int choice;
  printf(
      "1. Search by platform\n2. Search by username\n3. Search by password\n");
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
  default:
    printf("Invalid choice");
    exit(1);
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
  default:
    printf("Invalid choice");
    return;
  }
  char newValue[MAX_PAINTEXT_LEN];
  printf("Enter new %s: ", field);
  fgets(newValue, MAX_PAINTEXT_LEN, stdin);
  newValue[strcspn(newValue, "\n")] = 0;
  char *sql = malloc(sizeof(char) * 60 * 50);
  memset(sql, 0, sizeof(char) * 60 * 50);
  if (strcmp(field, "password") == 0) {
    size_t password_len = strlen(newValue);
    char *hashed_password = encrypt(newValue, key, nonce);
    sprintf(sql, "UPDATE main SET %s='%s',l='%ld' WHERE id=%d", field,
            hashed_password, password_len, id);
    sqlExecute(sql, NULL, NULL, NULL);
    return;
  }
  sprintf(sql, "UPDATE main SET %s='%s' WHERE id=%d", field, newValue, id);
  sqlExecute(sql, NULL, NULL, NULL);
}
void deleteEntry() {
  system("clear");
  int id = findId();
  char *sql = malloc(sizeof(char) * 60 * 50);
  memset(sql, 0, sizeof(char) * 60 * 50);
  sprintf(sql, "DELETE FROM main WHERE id=%d", id);
  sqlExecute(sql, NULL, NULL, NULL);
}

void showStored() {
  system("clear");
  char *sql = "SELECT * FROM main";
  // printAllFields();
  sqlExecute(sql, printAllPasswords, NULL, NULL);
}

void sqlExecute(char *sql, int (*callback)(void *, int, char **, char **),
                int (*failedCallBack)(), void *data) {
  sqlite3 *db;
  char *err_msg;
  int rc = sqlite3_open("passwords.db", &db);
  if (rc != SQLITE_OK) {
    printf("Connection to db failed.\nError: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(1);
  }
  rc = sqlite3_exec(db, sql, callback, data, &err_msg);
  if (rc != SQLITE_OK) {
    if (!failedCallBack) {
      printf("Error: %s", err_msg);
      sqlite3_free(err_msg);
      sqlite3_close(db);
      return;
    }
    failedCallBack();
  }
}

void validateDatabse() {
  char *sql = "CREATE TABLE IF NOT EXISTS main ("
              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
              "password TEXT,"
              "username TEXT,"
              "platform TEXT,"
              "l INT)";
  sqlExecute(sql, NULL, NULL, NULL);
}
int createMasterPassowrd() {
  char masterPassword[20];
  printf("Enter new master password: ");
  scanf("%s", masterPassword);
  char hashedMasterPassword[crypto_pwhash_STRBYTES];
  if (crypto_pwhash_str(hashedMasterPassword, masterPassword,
                        strlen(masterPassword), crypto_pwhash_OPSLIMIT_MIN,
                        crypto_pwhash_MEMLIMIT_MIN) != 0) {
    exit(1);
  }
  char *createTableQuery = malloc(MAX_QUERY_LEN);
  createTableQuery = "CREATE TABLE IF NOT EXISTS auth (password TEXT)";
  sqlExecute(createTableQuery, NULL, NULL, NULL);
  char *insertQuery = malloc(MAX_QUERY_LEN);
  memset(insertQuery, 0, MAX_QUERY_LEN);
  sprintf(insertQuery, "INSERT INTO auth (password) VALUES('%s')",
          hashedMasterPassword);
  sqlExecute(insertQuery, NULL, NULL, NULL);
  return 0;
}
int verifyPassword(void *password, int colCount, char **data, char **columns) {
  if (crypto_pwhash_str_verify(data[0], password, strlen(password)) != 0) {
    printf("Wrong Password!\n");
    exit(1);
  }
  return 0;
}
int autheticateUser() {
  char *sql = "SELECT * FROM auth";
  char inputPassword[20];
  printf("Enter Password: ");
  scanf("%s", inputPassword);
  sqlExecute(sql, verifyPassword, createMasterPassowrd, inputPassword);
  return 0;
}

int printAllPasswords(void *unused, int colCount, char **data, char **columns) {
  int i;
  for (i = 0; i < colCount; i++) {
    if (strcmp(columns[i], "l") == 0) {
      continue;
    }
    if (strcmp(columns[i], "password") == 0) {
      int len = atoi(data[colCount - 1]);
      char *decrypted = malloc(sizeof(char) * len);
      int status = decrypt(data[i], decrypted, len, key, nonce);
      if (status) {
        printf("%s : %.*s\n", columns[i], len, decrypted);
        continue;
      } else {
        printf("Decryption failed\n");
        continue;
      }
    }
    printf("%s : %s\n", columns[i], data[i] ? data[i] : "NULL");
  }
  printf("\n");
  return 0;
}
int printFieldsCallback(void *unused, int colCount, char **data,
                        char **columns) {
  printf("|\t");
  printf("%s ", data[1] ? data[1] : "NULL");
  printf("\t|");
  return 0;
}
void printAllFields() {
  char *sql = "PRAGMA table_info(main)";
  sqlExecute(sql, printFieldsCallback, NULL, NULL);
  printf("\n");
}
void printHelp() {
  printf("Try any of following: \n\n"
         "\tcpassmanager menu\n"
         "\t\t - This will show the menu.\n"
         "\tcpassmanager addnew\n"
         "\t\t - This will add new entry.\n"
         "\tcpassmanager searchby [field]\n"
         "\t\t - This will search the database by field(username,platform).\n"
         "\t\t - Example: cpassmanager searchby username\n"
         "\tcpassmanager all\n"
         "\t\t - This will show all the stored passwords.\n");
}
