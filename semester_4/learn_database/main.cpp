#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../sqlite3pp-master/headeronly_src/sqlite3pp.h"
//#include "../sqlite3pp-master/src/sqlite3ppext.h"

using namespace std;

int main() {
    sqlite3pp::database db("test.db");
 //   db.execute("INSERT INTO Users (name) VALUES (\"Greg\")");
    sqlite3pp::command cmd(
            db, "INSERT INTO contacts (name, phone) VALUES (?, ?)");
    cmd.binder() << "Grag" << "121";
    cmd.execute();

    sqlite3pp::query qry(db, "SELECT name, phone FROM contacts");

    for (int i = 0; i < qry.column_count(); ++i) {
        cout << qry.column_name(i) << "\t";
    }
    cout << endl;
    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
        for (int j = 0; j < qry.column_count(); ++j) {
            string a =(*i).get<char const*>(j);
            cout <<"&" << a << "&\t";
        }
        cout << endl;
    }
    std::cout << "Done.\n";
    return 0;
}