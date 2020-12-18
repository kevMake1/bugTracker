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
#include <iomanip>
#include <sstream>
#include <sqlite3.h>

#include "../Header/TestsPrototypes.h"

using namespace std;


//MARK:- Main

void showHeader();
void showCommands();
static int callback(void* data, int argc, char** argv, char** azColName);
static int callbackProjects(void* data, int argc, char** argv, char** azColName);
void displayProjects(sqlite3 *db);
void createProject(sqlite3 *db, string projectName);
void insert(sqlite3 *db, string projectName, string bugName, string description, string fixed);
void displayFromTable(sqlite3 *db, string query);

int main(int argc, const char * argv[]) {
    
    //title
    cout << "Bug Tracker\n\n\n";
    
    //open database
    sqlite3 *DB;
    int exit = 0;
    exit = sqlite3_open("BugTracker.db", &DB);
    
    if(exit){
        cerr << "Error opening DB" << sqlite3_errmsg(DB) << endl;
        //return (-1);
    } else{
        cout << "Open Database Successfully" << endl;
    }
    
    
    
    //MARK:-
    
    displayProjects(DB);
    
    
    string userInput;
    
    while(userInput != "exit"){
        
        cout << endl;
        getline(cin, userInput);
        
        string buff;     // buffer string
        stringstream ss(userInput);     // insert the string into a stream
        vector<string> commands;
        
        while(ss >> buff){
            commands.push_back(buff);
        }
        
        
        //if there is one argument
        if(commands.size() == 1){
            if(commands[0] == "help"){     //help
                showCommands();
            } else if(commands[0] == "exit") {     //exit
                continue;
            } else if(commands[0] == "clear"){      //clear
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            } else {
                cerr << "\nError: Command is not recognized.\n";
            }
        } //if there is two arguments
        else if(commands.size() == 2){
            if(commands[0] == "create"){        //create
                createProject(DB, commands[1]);
            } else if(commands[0] == "choose"){     //choose
                //choose project imp
                //while loop to stay in that project
            } else if(commands[0] == "delete"){     //delete
                //delete project imp
            }
            else {
                cerr << "\nError: command not recognized\n";
            }
        } else {
            cerr << "\n Error: too much arguments";
        }
        
    }
    
    
    //MARK:-
    
    cout << "\n\n";
    
    string query = "SELECT * FROM PERSON;";
    query = "SELECT BUGNAME FROM proj1 WHERE ID = 2;";
    //displayFromTable(DB, query);
    
    //delete
    //sql = "DELETE FROM PERSON WHERE ID = 2;";
    
    sqlite3_close(DB);
    

    
    return 0;
}

//MARK:- Functions

void showHeader(){
    
    cout << left << setw(35) << setfill(' ') << "Projects";
    cout << left << setw(11) << setfill(' ') << "# of bugs";
    cout << endl;
    cout << left << setw(46) << setfill('-') << "-";
    cout << endl;
}

void showCommands(){
    cout << "\nHere are some commands you can use:\n"
    << "create {project name}\n"
    << "choose {project name}\n"
    << "delete {project name}\n"
    << "clear\n";
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

//callback for getting projects
static int callbackProjects(void* data, int argc, char** argv, char** azColName){
    
    const char separator = ' ';
    const int nameWidth = 35, numWidth = 8;
    
    for(int i = 0; i < argc; i++){
        
        if(strcmp(argv[i], "sqlite_sequence") == 0) continue; //to not display 'sqlite_sequence'
        cout << left << setw(nameWidth) << setfill(separator) << argv[i];
        cout << left << setw(numWidth) << setfill(separator) << argc;
        cout << endl;
        
    }
    
    return 0;
}

void displayProjects(sqlite3 *db){
    
    string query = "SELECT name FROM sqlite_master WHERE type='table';";
    
    showHeader();
    sqlite3_exec(db, query.c_str(), callbackProjects, NULL, NULL);
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

