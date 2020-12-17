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
using namespace std;

#ifndef TestsPrototypes_h
#define TestsPrototypes_h

//MARK:- Project

class Project{
private:
    int numOfBugs;
    string projName;
public:
    Project(string name);
    int getNumOfBugs() const;
    string getProjName();
    void changeProjName(string s);
    void incrementNumOfBugs();
    void decrementNumOfBugs();
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

void Project::incrementNumOfBugs(){
    numOfBugs++;
}

void Project::decrementNumOfBugs(){
    numOfBugs--;
}

//MARK:- Bugs

class Bug{
private:
    string bugName;
    string description;
    
public:
    Bug(string name);
    string getBugName();
    string getDescription();
    void changeBugName(string s);
    void setDescription(string s);
    
};

Bug::Bug(string name){
    bugName = name;
}

string Bug::getBugName(){
    return bugName;
}

string Bug::getDescription(){
    return description;
}

void Bug::changeBugName(string s){
    bugName = s;
}

void Bug::setDescription(string s){
    description = s;
}


#endif /* TestsPrototypes_h */
