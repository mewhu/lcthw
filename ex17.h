#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address {
  int id;
  int set;
  char email[MAX_DATA];
  char name[MAX_DATA];
};

struct Database {
  struct Address rows[MAX_ROWS];
};

struct Connection {
  FILE *file;
  struct Database *db;
};

void die(const char *msg);
void printAddress(struct Address *);
void loadDB(struct Connection *conn);
struct Connection *openDB(const char *file_name, char mode);
void closeDB(struct Connection *conn);
void writeDB(struct Connection *conn);
void initDB(struct Connection *conn);
void setDB(struct Connection *conn, int id, const char *name, const char *email);
void getDB(struct Connection *conn, int id);
void deleteDB(struct Connection *conn, int id);
void listDB(struct Connection *conn);
