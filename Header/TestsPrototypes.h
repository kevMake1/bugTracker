//
//  TestsPrototypes.h
//  bugTracker
//
//  Created by Kevaughn Clarke on 12/15/20.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include "BugPrototype.h"

using namespace std;

#ifndef TestsPrototypes_h
#define TestsPrototypes_h

//MARK:- Project

class Project{
private:
    int numOfBugs;
    string projName;
    vector<Bug> bugs;
    
public:
    Project(string name);
    int getNumOfBugs() const;
    string getProjName();
    void changeProjName(string s);
    void addBug(string name);
    void addBug(string name, string des);
    void decrementNumOfBugs();
    void getBugs();
};

Project::Project(string name){
    projName = name;
    numOfBugs = 0;
}

int Project::getNumOfBugs() const{
    return numOfBugs;
}

string Project::getProjName(){
    return projName;
}

void Project::changeProjName(string s){
    
    projName = s;
    cout << "\nName Changed to " << projName << endl;
}

void Project::addBug(string name){
    bugs.push_back(Bug(name));
    numOfBugs++;
}
void Project::addBug(string name, string des){
    bugs.push_back(Bug(name, des));
    numOfBugs++;
}

void Project::decrementNumOfBugs(){
    numOfBugs--;
}

void Project::getBugs(){
    
    for(int i = 0; i < numOfBugs; i++){
        cout << bugs[i].getBugName() << "\t\t\t\t" << bugs[i].getDescription() << endl;
    }
}


#endif /* TestsPrototypes_h */
