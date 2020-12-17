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

void fillData(){
    
}



//MARK:- Main

void showProjects();

int main(int argc, const char * argv[]) {

    cout << "Bug Tracker\n\n\n";
    
    showProjects();
    

    
    return 0;
}

//MARK:- Functions

void showProjects(){
    cout << "Projects\t\t\t\t\t\t\t# of bugs\n";
    cout << "-------------------------------------------------\n";
    
    //fetch projects:
    for(int i = 0; i < projDatabase.size(); i++){
        cout << projDatabase[i].getProjName() << endl;
    }
    
    
}


