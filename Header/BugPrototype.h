//
//  BugPrototype.h
//  bugTracker
//
//  Created by Kevaughn Clarke on 12/17/20.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#ifndef BugPrototype_h
#define BugPrototype_h

class Bug{
private:
    string bugName;
    string description;
    
public:
    Bug(string name);
    Bug(string name, string des);
    string getBugName();
    string getDescription();
    void changeBugName(string s);
    void setDescription(string s);
    
};

Bug::Bug(string name){
    bugName = name;
}

Bug::Bug(string name, string des){
    bugName = name;
    description = des;
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


#endif /* BugPrototype_h */
