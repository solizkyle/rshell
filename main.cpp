#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <string.h>
#include <stdio.h>
#include <sstream>
using namespace std;

//TODO:
//  Add execute functionality to both classes
//  Write function to delete everything after a # (fix comments)

class Shell{
    public:
        Shell* first;
        Shell* second;
        Shell(){};
        virtual bool execute() = 0;
};

class Connector : public Shell{
    public: 
        // Shell* first;
        // Shell* second;
        Connector() : Shell(){};
        Connector(Shell* f, Shell* s){
            first = f;
            second = s;
        };
        virtual bool execute() = 0; // for compiler
};

class Bars : public Connector{
    public: 
        Bars() : Connector (){};
        Bars(Shell* f, Shell* s) : Connector(f, s){};
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
        Semi(Shell* f, Shell* s) : Connector(f, s){};
        bool execute(){
            cout << "executing tree" << endl;
            first->execute();
            cout << "executed first" << endl;
            return second->execute();
        }
};

class Amp : public Connector{
    public:
        Amp() : Connector (){};
        Amp(Shell* f, Shell* s) : Connector(f, s){};
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
            
        // //real execute
        // pid_t pid;
        // int status;
        // //forks the process
        // if((pid = fork()) < 0){ //if fork() failed
        //     cout << "Error: fork failed" << endl;
        //     return false;
        // }
        // else if(pid == 0){ //if this is the child process
            
        // }
        // else{ //if it is the parent process
        //     while()
        // }
    }
};

Shell* stringToCommand(string commandLine){
    cout << "starting stringToCommand" << endl;
    stringstream ss;
    ss << commandLine;
    // //sets up everything to use stringstream
    //builds new command
    Command* temp = new Command;
    string tempString;
    ss >> tempString;
    temp->cmd = tempString.c_str();
    //takes in any potential arguments
    while(ss >> tempString){
        temp->args.push_back(tempString);
    }
    return temp;
}

void parse(string commandLine){

    Shell* top = NULL;
    for(int i = 0; i < commandLine.size(); ++i){
        string temp;
        if(commandLine.at(i) == ';'){
            //make substr
            temp = commandLine.substr(0, i);
            //delete what we took
            commandLine.erase(0, i + 1);
            //reset i
            i = 0;
            //issue where it never enteres the first if statement
            if(top == NULL){
                cout << "top is empty" << endl;
                Shell* connect = new Semi;
                top = connect;
                //Shell* 
                connect->first = stringToCommand(temp);
            }
            else{
                cout << "top is not empty" << endl;
                Shell* connect = new Semi(top, stringToCommand(temp));
                // connect->first = top;
                // top->second = stringToCommand(temp);
                top = connect;
            }
        }
        else if(commandLine.at(i) == '|'){
            if(commandLine.at(i + 1) == '|'){
                //make substr
                temp = commandLine.substr(0, i);
                //delete what we took
                commandLine.erase(0, i + 2);    //see below for deleting both connectors
                //reset i
                i = 0;
                if(top == NULL){
                    Shell* connect = new Bars;
                    top = connect;
                    connect->first = stringToCommand(temp);
                    top->execute();
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
            if(commandLine.at(i + 1) == '&'){
                //make substr
                temp = commandLine.substr(0, i);
                //delete what we took
                commandLine.erase(0, i + 2);    //need to change it so that it deletes both connectors  
                //reset i
                i = 0;
                if(top == NULL){
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
    }
    string temp = commandLine;
    if(top == NULL){
        top = stringToCommand(temp);
    }
    else{
        top->second = stringToCommand(temp);
    }
    cout << "going to execute!" << endl;
    top->execute();
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
// change
