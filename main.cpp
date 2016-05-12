#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

//TODO:
//  Create parse function
//  Add execute functionality to both classes
//  Write loop in main function


class Shell{
    virtual bool execute() = 0;
};

class Connector: public Shell{
    //IDs: 1 = || 2 = && 3 = ;
    int ID;
    Shell* First;
    Shell* Second;
    bool execute(){
        return true;
    }
};

class Command: public Shell{
    char cmd[];
    vector<string> args;
    bool execute(){
        return true;
    }
};

void parse(string commandLine){
    string tempString;
    stringstream ss;
    ss >> tempString;
    
}

int main() {
    string commandLine;
    //output basic prompt
    while(commandLine != "exit"){
        cout << '$';
        getline(cin, commandLine);
        parse(commandLine);
    }
    return 0;
}
