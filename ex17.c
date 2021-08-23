#include "ex17.h"

void die(const char *msg) {
  if(errno) {
    perror(msg);
  } else {
    printf("ERROR: %s\n", msg);
  }
  exit(1);
}

void printAddress(struct Address *addr) {
  if(addr) {
    printf("ID:%4d, name:%s, email:%s\n", addr->id, addr->name, addr->email);
  } else {
    die("address not available");
  }
}

void loadDB(struct Connection *conn) {
  if(conn) {
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc != 1) {
      die("failed to load Database");
    }
  } else {
    die("conn is not available");
  }
}

struct Connection *openDB(const char *file_name, char mode) {
  struct Connection *conn = malloc(sizeof(struct Connection));
  if(conn) {
    conn->db = malloc(sizeof(struct Database));
    if(conn->db){
      if(mode == 'c') {
        conn->file = fopen(file_name, "w");
      } else {
        // [Mew][Note#1] if db_file does not exist, the fopen(,"r+") would set 
        //               errno. Then we could use the perror in function die() to display
        conn->file = fopen(file_name, "r+");
        if(conn->file) {
          loadDB(conn);
        }
      }
      if(!conn->file) {
        die("failed to open file");
      }
    } else {
      die("could not malloc Database for conn->db");
    }
  } else {
    die("could not malloc Connection in openDB()");
  }
  return conn;
}

void closeDB(struct Connection *conn) {
  if(conn) {
    fclose(conn->file);
    free(conn->db);
    free(conn);
    // conn->db->rows
  } else {
    die("failed to closeDB due to conn invalid");
  }
}

void writeDB(struct Connection *conn) {
  if(conn) {
    if(conn->file) {
      rewind(conn->file);
      int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
      if(rc != 1) {
        die("failed to writeDB due to fwrite failure");
      }
      rc = fflush(conn->file);
      if(rc != 0){
        die("failed to fflush conn->file");
      }
    } else {
      die("failed to fwrite due to invalid conn->file");
    }
  } else {
    die("failed to writeDB due to invalid conn");
  }
}

void initDB(struct Connection *conn) {
  int i = 0;
  for(i=0; i<MAX_ROWS; i++){
    // [Mew] following uses call_by_value to assign value to conn->db->rows[i]
    // [Mew] So, we do not care the exact object address of prototype_addr
    struct Address prototype_addr = { .id = i, .set = 0 };
    conn->db->rows[i] = prototype_addr;
  }
}

void setDB(struct Connection *conn, int id, const char *name, const char *email) {
  struct Address *addr = &conn->db->rows[id];
  if(addr->set) {
    die("The addr is already set");
  }
  addr->set = 1;
  strncpy(addr->name, name, MAX_DATA);
  addr->name[MAX_DATA-1] = '\0';
  strncpy(addr->email, email, MAX_DATA);
  addr->email[MAX_DATA-1] = '\0';
}

void getDB(struct Connection *conn, int id) {
  struct Address *addr = &conn->db->rows[id];
  if(addr->set) {
    printAddress(addr);
  } else {
    die("this ID is not set");
  }
}

void deleteDB(struct Connection *conn, int id) {
  /*
  struct Address *addr = &conn->db->rows[id];
  addr->set = 0;
  */
  struct Address proto_addr_for_init = { .id = id, .set = 0 };
  *((conn->db->rows) + id) = proto_addr_for_init;
}

void listDB(struct Connection *conn) {
  int i = 0;
  struct Database *db = conn->db;
  for(i = 0; i < MAX_ROWS; i++) {
    struct Address *cur = &db->rows[i];
    if(cur->set) {
      printAddress(cur);
    }
  }
}

int main(int argc, char *argv[]) {
  if(argc < 3) {
    die("USAGE: ex17 <dbfile> <action> [action params]");
  }
  const char *db_file_name = argv[1];
  const char action_char = argv[2][0];
  int id = 0;
  if(argc > 3) id = atoi(argv[3]);
  if(id >= MAX_ROWS) die("There's not that many records.");
  struct Connection *conn = openDB(db_file_name, action_char);

  switch(action_char) {
    case 'c':
      initDB(conn);
      writeDB(conn);
      break;
    case 'g':
      if(argc != 4) die("need an id to get");
      getDB(conn, id);
      break;
    case 's':
      if(argc != 6) die("need id, name, email to set");
      setDB(conn, id, argv[4], argv[5]);
      writeDB(conn);
      break;
    case 'd':
      if(argc != 4) die("need an id to delete");
      deleteDB(conn, id);
      writeDB(conn);
      break;
    case 'l':
      listDB(conn);
      break;
    default:
      die("Invalid action\n");
      break;
  }
  closeDB(conn);
  return 0;
}
