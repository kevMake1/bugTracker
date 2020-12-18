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
void createProject(sqlite3 *db, string projectName);
void insert(sqlite3 *db, string projectName, string bugName, string description, string fixed);
void displayFromTable(sqlite3 *db, string query);

int main(int argc, const char * argv[]) {

    cout << "Bug Tracker\n\n\n";
    
    sqlite3 *DB;
    //open database
    
    int exit = 0;
    exit = sqlite3_open("test.db", &DB);
    
    if(exit){
        cerr << "Error opening DB" << sqlite3_errmsg(DB) << endl;
        //return (-1);
    } else{
        cout << "Open Database Successfully" << endl;
    }
    
    
    
    //MARK:- test
    //string testt = "SELECT name FROM test.sqlite_master WHERE type='table';";
    string testt = "SELECT name FROM sqlite_master WHERE type='table';";
    string t;
    sqlite3_exec(DB, testt.c_str(), callback, NULL, NULL);
    
    
    
    //MARK:-
    

    
    
    string query = "SELECT * FROM PERSON;";
    query = "SELECT BUGNAME FROM proj1 WHERE ID = 2;";
    displayFromTable(DB, query);
    
    //delete
    //sql = "DELETE FROM PERSON WHERE ID = 2;";
    
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



void createProject(sqlite3 *db, string projectName){
    
    string sql = "CREATE TABLE if not exists " + projectName + "("
                "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                "BUGNAME           TEXT    NOT NULL, "
                "DESCRIPTION       TEXT, "
                "FIXED             CHAR(1)     NOT NULL, "
                "SOLUTION          TEXT ); ";
    
    //Create table
    char *messageErr;
    int exit = 0;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageErr);
    
    if(exit != SQLITE_OK){
        cerr << "Error creating table" << endl;
        sqlite3_free(messageErr);
    } else {
        cout << "table create Successfully" << endl;
    }
}

void insert(sqlite3 *db, string projectName, string bugName, string description, string fixed){
    
    char *messageErr2;
    string sql = "INSERT INTO "+ projectName +"(BUGNAME, DESCRIPTION, FIXED) VALUES('"+ bugName +"', '"+ description +"', '"+ fixed +"');";

  
    
    int exit = 0;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageErr2);
    
    if(exit != SQLITE_OK){
        cerr << "Error inserting" << endl;
        sqlite3_free(messageErr2);
    } else {
        cout << "Insert Successfully" << endl;
    }
}

void displayFromTable(sqlite3 *db, string query){
    
    sqlite3_exec(db, query.c_str(), callback, NULL, NULL);
}

