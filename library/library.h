#include <sqlite3.h>
#define MAX_QUERY_LEN sizeof(char) * 50 * 40
void addEntry();
void showMenu();
void editEntry();
void showStored();
void validateDatabse();
void deleteEntry();
void help();
void sqlExecute(char *sql, int (*callback)(void *, int, char **, char **),
                int (*failedCallBack)(), void *data);
void searchBy(char *searchField);
void printAllFields();
int printAllPasswords(void *data, int argc, char **argv, char **azColName);
int printFieldsCallback(void *data, int argc, char **argv, char **azColName);
int verifyUser();
int autheticateUser();
void printHelp();
