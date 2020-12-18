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
void showBugsHeader();
void showCommands();
void showCommandsForBugs();
void chosenProjectProgram(sqlite3 *db, string projName);
static int callback(void* data, int argc, char** argv, char** azColName);
static int callbackProjects(void* data, int argc, char** argv, char** azColName);
static int callbackBugs(void* data, int argc, char** argv, char** azColName);
static int callbackBugDescrpiton(void* data, int argc, char** argv, char** azColName);
void displayProjects(sqlite3 *db);
void createProject(sqlite3 *db, string projectName);
void createBug(sqlite3 *db, string projectName, string bugName, string description, string fixed);
void displayFromTable(sqlite3 *db, string query);
void displayBugs(sqlite3 *db, string projName);

int main(int argc, const char * argv[]) {
    
    //title
    cout << "Bug Tracker\n\n";
    
    //open database
    sqlite3 *DB;
    int exit = 0;
    exit = sqlite3_open("BugTracker.db", &DB);
    
    if(exit){
        cerr << "Error opening DB" << sqlite3_errmsg(DB) << endl;
        //return (-1);
    } else{
        //cout << "Open Database Successfully" << endl;
    }
    
    
    
    //MARK:-
    
    displayProjects(DB);
    
    string query;
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
                cout << "\n\n\n\n\n\n\n\n\n"
                << "\n\n\n\n\n\n\n\n\n\n\n"
                << "\n\n\n\n\n\n\n\n\n\n";
            } else if(commands[0] == "show"){   //show
                displayProjects(DB);
            } else {
                cerr << "\nError: command '" + commands[0] + "' is not recognized\n";
            }
        } //if there is two arguments
        else if(commands.size() == 2){
            if(commands[0] == "create"){        //create
                createProject(DB, commands[1]);
            } else if(commands[0] == "choose"){     //choose
                //choose project imp
                //while loop to stay in that project
                chosenProjectProgram(DB, commands[1]);
            } else if(commands[0] == "delete"){     //delete
                //delete project imp
                query = "DROP TABLE " + commands[1] + ";";
                int err = sqlite3_exec(DB, query.c_str(), NULL, NULL, NULL);
                if(err){
                    cerr << "\nError: no project with the name of " + commands[1] + ".\n";
                } else{
                    cout << "\nThe project '" + commands[1] + "' was successfully deleted.\n";
                }
                
            }
            else {
                cerr << "\nError: command '" + commands[0] + "' is not recognized\n";
            }
        } else {
            cerr << "\nError: too much arguments\n";
        }
        
    }
    
    
    //MARK:-
    
    cout << "\n\n";
    
    sqlite3_close(DB);
    

    
    return 0;
}

//MARK:- Functions

void showHeader(){
    
    cout << left << setw(35) << setfill(' ') << "\nProjects";
    cout << left << setw(11) << setfill(' ') << "# of bugs";
    cout << endl;
    cout << left << setw(46) << setfill('-') << "-";
    cout << endl;
}

void showBugsHeader(){
    cout << left << setw(12) << setfill(' ') << "\nBug ID";
    cout << left << setw(35) << setfill(' ') << "BugName";
    cout << left << setw(11) << setfill(' ') << "Fixed?";
    cout << endl;
    cout << left << setw(55) << setfill('-') << "-";
    cout << endl;
}

void showCommands(){
    cout << "\nHere are some commands you can use:\n"
    << "create {project name}\n"
    << "choose {project name}\n"
    << "delete {project name}\n"
    << "clear\n"
    << "show\n"
    << "exit\n";
}

void showCommandsForBugs(){
    cout << "\nHere are some commands you can use:\n"
    << "create {bug name}\n"
    << "choose {bug ID}\n"
    << "delete {bug ID}\n"
    << "change {ID} {what to edit} {option}\n"
    << "\t-what to edit: bugname, description, fixed (options: y/n), solution\n"
    << "clear\n"
    << "show\n"
    << "exit\n";
}

void chosenProjectProgram(sqlite3 *db, string projName){
    //show bugs
    displayBugs(db, projName);
    
    //add bugs
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
                showCommandsForBugs();
            } else if(commands[0] == "exit") {     //exit
                break;
            } else if(commands[0] == "clear"){      //clear
                cout << "\n\n\n\n\n\n\n\n\n"
                << "\n\n\n\n\n\n\n\n\n\n\n"
                << "\n\n\n\n\n\n\n\n\n\n";
            } else if(commands[0] == "show"){   //show
                displayBugs(db, projName);
            } else {
                cerr << "\nError: command '" + commands[0] + "' is not recognized\n";
            }
        } //if there is two arguments
        else if(commands.size() == 2){
            if(commands[0] == "create"){        //create
                string fixed;
                
                bool done = false;
                
                while(!done){
                    cout << "\nIs it fixed (y/n)?: ";
                    cin >> fixed;
                    if(fixed == "y" || fixed == "n"){
                        done = true;
                    } else{
                        cout << "\nError: input '" + fixed + "' not valid, try again.";
                    }
                }
                
                string description;
                //string line;
                string buf;
                
                cout << "\nDescription:\n";
                
                getline(cin, buf);
                
                getline(cin, description);
                
                createBug(db, projName, commands[1], description, fixed);
                
                
            } else if(commands[0] == "choose"){     //choose
                //choose bug imp
                string query = "SELECT DESCRIPTION FROM " + projName + " WHERE ID = " + commands[1] + ";";
                
                cout << endl;
                sqlite3_exec(db, query.c_str(), callbackBugDescrpiton, NULL, NULL);
                
            } else if(commands[0] == "delete"){     //delete
                //delete bug imp
                string query = "DELETE FROM " + projName + " WHERE ID = " + commands[1] + ";";
                int err = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
                if(err){
                    cerr << "\nError: no bug with the Bug ID of " + commands[1] + ".\n";
                } else{
                    cout << "\nThe bug with BugID: '" + commands[1] + "' was successfully deleted.\n";
                }
                
            }
            else {
                cerr << "\nError: command '" + commands[0] + "' is not recognized\n";
            }
        } else if(commands.size() == 4){ //four arguments
            if(commands[0] == "change"){    //change {ID} {command} {option}
                if(commands[2] == "fixed"){ //change fixed
                    
                    if(commands[3] == "y" || commands[3] == "n"){
                        string query = "UPDATE " + projName + " SET FIXED = '" + commands[3] + "' WHERE ID = " + commands[1] + ";";
                        sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
                        cout << "\nchange sucessful.\n";
                    } else{
                        cout << "\nError: input '" + commands[3] + "' not valid, try again.";
                    }
                    
                } else if(commands[2] == "des"){ //change description
                    
                } else if(commands[2] == "sol"){   //change solution
                    
                } else if(commands[2] == "bugname"){    //change bug name
                    
                }
            }
        }
        else {
            cerr << "\nError: too much arguments\n";
        }
        
    }
    //choose bug
    //enter editing stage
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
    const int nameWidth = 35;
    
    for(int i = 0; i < argc; i++){
        
        if(strcmp(argv[i], "sqlite_sequence") == 0) continue; //to not display 'sqlite_sequence'
        cout << left << setw(nameWidth) << setfill(separator) << argv[i];
        //cout << left << setw(numWidth) << setfill(separator) << argc;
        cout << endl;
        
    }
    
    return 0;
}

//callback for getting bugs
static int callbackBugs(void* data, int argc, char** argv, char** azColName){
    
    const char separator = ' ';
    
    cout << left << setw(11) << setfill(separator) << argv[0];
    cout << left << setw(35) << setfill(separator) << argv[1];
    cout << left << setw(3) << setfill(separator) << argv[3];
    
    cout << endl;
    
    return 0;
}

    
//callback for getting bug description
static int callbackBugDescrpiton(void* data, int argc, char** argv, char** azColName){
    
    cout << argv[0];
    
    cout << endl;
        
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
        cout << "Project create successfully" << endl;
    }
}

void createBug(sqlite3 *db, string projectName, string bugName, string description, string fixed){
    
    char *messageErr2;
    

    string sql = "INSERT INTO "+ projectName +"(BUGNAME, DESCRIPTION, FIXED) VALUES('"+ bugName +"', '"+ description +"', '"+ fixed +"');";

  
    
    int exit = 0;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageErr2);
    
    if(exit != SQLITE_OK){
        cerr << "Error inserting" << endl;
        sqlite3_free(messageErr2);
    } else {
        cout << "\nCreate Bug Successfully" << endl;
    }
}

void displayFromTable(sqlite3 *db, string query){
    
    sqlite3_exec(db, query.c_str(), callback, NULL, NULL);
}

void displayBugs(sqlite3 *db, string projName){
    showBugsHeader();
    string sql = "SElECT * FROM " + projName + ";";
    sqlite3_exec(db, sql.c_str(), callbackBugs, NULL, NULL);
}


