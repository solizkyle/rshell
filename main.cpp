#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;

//TODO:
//  Create parse function
//  Add execute functionality to both classes
//  Write loop in main function


class Shell{
    virtual bool execute() = 0;
};

class Connector : public Shell{
    Shell* First;
    Shell* Second;
    virtual bool execute() = 0;
};

class Bars : public Connector{
    bool execute(){
        return true;
    }
};

class Semi : public Connector{
    bool execute(){
        return true;
    }
};

class Amp : public Connector{
    bool execute(){
        return true;
    }
};

class Command : public Shell{
    char cmd[];
    vector<string> args;
    bool execute(){
        return true;
    }
};

void parse(string commandLine){
    char* cmdLine = new char[commandLine.length() + 1];

    vector<string> commands;
    vector<string> connectors;
    for(int i = 0; i < commandLine.size(); ++i){
        if(commandLine.at(i) == ';'){
            //make substr
            //delete what we took
            //reset i
        }
        else if(commandLine.at(i) == '|'){
            if(commandLine.at(i + 1) == '|'){
                //make substr
            }
        }
        else if(commandLine.at(i) == '&'){
            if(commandLine.at(i + 1) == &){
                //make substr
            }
        }
        else{
            //make substr
        }
    }
    
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
