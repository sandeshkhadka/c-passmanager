#include <sqlite3.h>

void addEntry();
void showMenu();
void editEntry();
void showStored();
void validateDatabse();
void help();
int callback(void *data, int argc, char **argv, char **azColName);
sqlite3 *connectdb();

