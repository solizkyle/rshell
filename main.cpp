#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

//TODO:
//  Write function to delete everything after a # (fix comments)
//  Bug where you have to write exit twice to actually exit
//  Finish execute()
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
            first->execute();
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
        string cmd; // is it becuase you're trying to change a const?
        vector<string> args;
        Command() : Shell(){};
        Command(string c, vector<string> a) : Shell(), cmd(c), args(a) {};
        bool execute(){
            // cout << "Executed Command: " << (const char *)cmd.c_str() << endl;
            // return true;
            //real execute
            //need to convert vector of args to a single string
            string argument;
            for(unsigned i = 0; i < args.size(); ++i){
                argument = argument + " " + args.at(i);
            }
            cout << "entire command: " << argument << endl;
            char** tokens;
            // tokens = new char*[argument.size() + 1];
            // strcpy(*tokens)
            
            char** tok;
            tok = new char*[cmd.size() +1];
            *tok = strtok(*tok, " ");
            //char temp = cmd.c_str();
            //char* command = &temp;
            tokens = new char*[argument.size() + 1];
            strcpy(*tok, argument.c_str());
            *tokens = strtok(*tokens, " ");
            //const char * c = argument.c_str();
            pid_t pid;
            int status;
            //forks the process
            if((pid = fork()) < 0){ //if fork() failed
                cout << "Error: fork failed" << endl;
                return false;
            }
            else if(pid == 0){ //if this is the child process
                //do stuff
                
                if(execvp(tok[0], tokens) < 0){   //executes the command: if it fails, returns -1, else continue
                    return false;
                }
            }
            else{ //if it is the parent process
                while(wait(&status) != pid)
                ;
            }
            return true;
    }
};

Shell* stringToCommand(string commandLine){
    stringstream ss;
    ss << commandLine;
    // //sets up everything to use stringstream
    //builds new command
    Command* temp = new Command;
    string tempString;
    ss >> tempString;
    temp->cmd = tempString;
    //takes in any potential arguments
    while(ss >> tempString){
        temp->args.push_back(tempString);
    }
    return temp;
}

void parse(string commandLine){

    Shell* top = NULL;
    for(unsigned i = 0; i < commandLine.size(); ++i){
        string temp;
        if(commandLine.at(i) == ';'){
            //make substr
            temp = commandLine.substr(0, i); // didn't include actual character
            //delete what we took
            commandLine.erase(0, i + 1);
            //reset i
            i = 0;
            //issue where it never enteres the first if statement
            if(top == NULL){
                Shell* connect = new Semi;
                top = connect;
                //Shell* 
                connect->first = stringToCommand(temp);
            }
            else{
                Shell* connect = new Semi;
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
    top->execute();
}

int main() {
    string commandLine;
    while(cout << '$' && getline(cin, commandLine) && commandLine != "exit"){
        parse(commandLine);
    }
    return 0;
}
// changes made: changed while loop to exit correctly
// fixed problem. i think it had to do with polymorphism
// basically, just store cmd as a string. and when you want to use it
// cast it as (const char *)cmd.c_str()
