#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <string.h>
#include <stdio.h>
#include <sstream>
using namespace std;

//TODO:
//  Create parse function
//  Add execute functionality to both classes
//  Write loop in main function


class Shell{
    public:
        Shell(){};
        virtual bool execute() = 0;
};

class Connector : public Shell{
    public: 
        Shell* first;
        Shell* second;
        Connector() : Shell(){};
        Connector(Shell* f, Shell* r) : first(f), second(s){};
        virtual bool execute() = 0; // for compiler
};

class Bars : public Connector{
    public: 
        Bars() : Connector (){};
        Bars(Shell* f, Shell* s) : Connector(f, s);
        bool execute(){
            if(!first->execute()){
                return second->execute();
            }
            return true;
        }
};

class Semi : public Connector{
    public:
        Semi() : Connector (){};
        Semi(Shell* f, Shell* s) : Connector(f, s);
        bool execute(){
            first->execute();
            return second->execute();
        }
};

class Amp : public Connector{
    public:
        Amp() : Connector (){};
        Amp(Shell* f, Shell* s) : Connector(f, s);
        bool execute(){
            if(first->execute()){
                return second->execute();
            }
            return false; // else
        }
};

class Command : public Shell{
    public:
        const char* cmd;
        vector<string> args;
        
        Command() : Shell(){};
        Command(char c[], vector<string> a) : Shell(), cmd(c), args(a) {};
        bool execute(){
            cout << "executed command" << endl;
            return true;
        }
};

Shell* stringToCommand(string commandLine){
    stringstream ss;
    ss << commandLine;
    // //sets up everything to use strtok
    // char* cmdLine = new char[cmd.length() + 1];
    // const char s[2] = " ";
    // char *token;
    // token = strtok(cmdLine, s);
    //builds new command
    Command* temp = new Command;
    string tempString;
    ss >> tempString;
    temp->cmd = tempString.c_str();
    while(ss >> tempString){
        temp->args.push_back(tempString);
    }
    // if(token != NULL){

    // }
    // while(token != NULL){
    //     temp->args.push_back(token);
    //     token = strtok(NULL, s);
    // }
    return temp;
}

void parse(string commandLine){

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
