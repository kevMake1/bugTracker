//
//  main.cpp
//  bugTracker
//  
//  Created by Kevaughn Clarke on 12/3/20.
// 

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <sqlite3.h>

#include "../Header/TestsPrototypes.h"

using namespace std;

//MARK:- Temp

vector<Project> projDatabase = {Project("test1"), Project("test2")};


//MARK:- Global vars



//MARK:- Main

void showProjects();
static int callback(void* data, int argc, char** argv, char** azColName);
void openDatabase(sqlite3 *db);
void createTable(sqlite3 *db, string sql);

int main(int argc, const char * argv[]) {

    cout << "Bug Tracker\n\n\n";
    
    sqlite3 *DB;
    
    openDatabase(DB);
    
    //Create table
    string sql = "CREATE TABLE PERSON("
                "ID INT PRIMARY KEY     NOT NULL, "
                "NAME           TEXT    NOT NULL, "
                "SURNAME          TEXT     NOT NULL, "
                "AGE            INT     NOT NULL, "
                "ADDRESS        CHAR(50), "
                "SALARY         REAL );";
    
    char *messageErr;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageErr);
    
    if(exit != SQLITE_OK){
        cerr << "Error creating table" << endl;
        sqlite3_free(messageErr);
    } else {
        cout << "table create Successfully" << endl;
    }
    
    //Insert
    char *messageErr2;
    string query = "SELECT * FROM PERSON;";
    
    sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
    sql = "INSERT INTO PERSON VALUES(1, 'STEVE', 'GATES', 30, 'PALO ALTO', 1000.0);"
                   "INSERT INTO PERSON VALUES(2, 'BILL', 'ALLEN', 20, 'SEATTLE', 300.22);"
                   "INSERT INTO PERSON VALUES(3, 'PAUL', 'JOBS', 24, 'SEATTLE', 9900.0);";
    
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageErr2);
    
    if(exit != SQLITE_OK){
        cerr << "Error inserting" << endl;
        sqlite3_free(messageErr2);
    } else {
        cout << "Insert Successfully" << endl;
    }
    
    //delete
    sql = "DELETE FROM PERSON WHERE ID = 2;";
    
    sqlite3_close(DB);
    

    
    return 0;
}

//MARK:- Functions

void showProjects(){
    cout << "Projects\t\t\t\t\t\t\t# of bugs\n";
    cout << "-------------------------------------------------\n";
    
    projDatabase[0].addBug("bug1", "This is the description for the bug");
    
    //fetch projects:
    for(int i = 0; i < projDatabase.size(); i++){
        cout << projDatabase[i].getProjName() << "\t\t\t\t" << projDatabase[i].getNumOfBugs() <<endl;
    }
    
    
    
    projDatabase[0].getBugs();
    
}

//MARK:- Database functions

//callback for SQLite
static int callback(void* data, int argc, char** argv, char** azColName){
    
    fprintf(stderr, "%s: ", (const char*)data);
    
    for(int i = 0; i < argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    
    cout << endl;
    return 0;
}

void openDatabase(sqlite3 *db){
    //open database
    
    int exit = 0;
    exit = sqlite3_open("test.db", &db);
    
    if(exit){
        cerr << "Error opening DB" << sqlite3_errmsg(DB) << endl;
        //return (-1);
    } else{
        cout << "Open Database Successfully" << endl;
    }
}

void createTable(sqlite3 *db, string sql){
    
    //Create table
    char *messageErr;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageErr);
    
    if(exit != SQLITE_OK){
        cerr << "Error creating table" << endl;
        sqlite3_free(messageErr);
    } else {
        cout << "table create Successfully" << endl;
    }
}

