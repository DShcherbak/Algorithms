#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../sqlite3pp-master/headeronly_src/sqlite3pp.h"
//#include "../sqlite3pp-master/src/sqlite3ppext.h"

int main() {
    sqlite3pp::database db("test.db");
 //   db.execute("INSERT INTO Users (name) VALUES (\"Greg\")");
    sqlite3pp::command cmd(
            db, "INSERT INTO contacts (name, phone) VALUES (?, ?)");
    cmd.binder() << "Mike" << "555-1234";
    cmd.execute();
    std::cout << "Done.\n";
    return 0;
}