//
//  TestsPrototypes.h
//  bugTracker
//
//  Created by Kevaughn Clarke on 12/15/20.
//

#include <stdio.h>
#include <iostream>
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
    int getNumOfBugs();
    string getProjName();
    void incrementNumOfBugs();
    void decrementNumOfBugs();
};

Project::Project(string name){
    projName = name;
    numOfBugs = 0;
}

int Project::getNumOfBugs(){
    return numOfBugs;
}

string Project::getProjName(){
    return projName;
}

void Project::incrementNumOfBugs(){
    numOfBugs++;
}

void Project::decrementNumOfBugs(){
    numOfBugs--;
}



#endif /* TestsPrototypes_h */
