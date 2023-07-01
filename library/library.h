#include <sqlite3.h>

void addEntry();
void showMenu();
void editEntry();
void showStored();
void validateDatabse();
void help();
void sqlExecute(char *sql, int (*callback)(void*,int,char**,char**));
void searchBy(char *searchField);
void printAllFields();
int printCallback(void *data, int argc, char **argv, char **azColName);
int printFieldsCallback(void *data, int argc, char **argv, char **azColName);
