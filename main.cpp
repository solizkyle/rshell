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
    public:
        virtual bool execute() = 0;
};

class Connector : public Shell{
    Shell* first;
    Shell* second;
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

Base* stringToCommand(string cmd){
    
}

void parse(string commandLine){
    char* cmdLine = new char[commandLine.length() + 1];
    Shell* top = NULL;
    vector<string> commands;
    vector<string> connectors;
    for(int i = 0; i < commandLine.size(); ++i){
        string temp;
        if(commandLine.at(i) == ';'){
            //make substr
            temp = commandLine.substr(0, i);
            //delete what we took
            commandLine.erase(0, i);
            //reset i
            i = 0;
            if(top = NULL){
                Shell* connect = new Semi;
                top = connect;
                connect->first = stringToCommand(temp);
            }
            else{
                Shell connect = new Semi;
                connect->first = top;
                top->second = stringToCommand(temp);
                top = connect;
            }
        }
        else if(commandLine.at(i) == '|'){
            if(commandLine.at(i + 1) == '|'){
                //make substr
                temp = commandLine.substr(0, i);
                //delete what we took
                commandLine.erase(0, i);
                //reset i
                i = 0;
                if(top = NULL){
                    Shell* connect = new Bars;
                    top = connect;
                    connect->first = stringToCommand(temp);
                }
                else{
                    Shell* connect = new Bars;
                    connect->first = top;
                    top->second = stringToCommand(temp);
                    top = connect;
                }
            }
        }
        else if(commandLine.at(i) == '&'){
            if(commandLine.at(i + 1) == &){
                //make substr
                temp = commandLine.substr(0, i);
                //delete what we took
                commandLine.erase(0, i);
                //reset i
                i = 0;
                if(top = NULL){
                    Shell* connect = new Amp;
                    top = connect;
                    connect->first = stringToCommand(temp);
                }
                else{
                    Shell* connect = new Amp;
                    connect->first = top;
                    top->second = stringToCommand(temp);
                    top = connect;
                }
            }
        }
        else{
            //make substr
            temp = commandLine.substr(0, i);
            //if top != null, top->second = stringToCommand
            if(top == NULL){
                top = stringToCommand(temp);
            }
            else{
                top->second = stringToCommand(temp);
            }
            //if top == null, top = stringToCommand
        }
    }
    
}

int main() {
    string commandLine;
    while(commandLine != "exit"){
        cout << '$';
        getline(cin, commandLine);
        parse(commandLine);
    }
    return 0;
}
