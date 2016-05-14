#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

//TODO:
//  Write testcases for this program (scripts)
//  Test this program on the hammer server before uploading
//  Write the README.md
//  Merge the branches and add the "hw" tag
//  Create submission file
//  Virtual function delete


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
            if(cmd == "exit"){
                exit(0);
            }
            //size of argv
            int size = args.size() + 2;
            //
            char **argv = new char*[args.size() + 2];
            char *tempcmd = new char[cmd.size()];
            strcpy(tempcmd, cmd.c_str());
            argv[0] = tempcmd;
            for(unsigned i = 0; i < args.size(); ++i){
                char *temparg = new char[args.at(i).size()];
                strcpy(temparg, args.at(i).c_str());
                argv[i + 1] = temparg;
            }
            argv[size - 1] = NULL;
            
            pid_t pid;
            //int status;
            //forks the process
            if((pid = fork()) < 0){ //if fork() failed
                perror("Fork failed");
                return false;
            }
            else if(pid == 0){ //if this is the child process
                //do stuff
                if(execvp(argv[0], argv) < 0){   //executes the command: if it fails, returns -1, else continue
                    perror("Command Failed :^)");
                    exit(EXIT_FAILURE);
                }
                
                //exit(0);
            }
            else{ //if it is the parent process
                int status;
                waitpid(pid, &status, WUNTRACED | WCONTINUED);
                if(WIFEXITED(status)){
                    if(WEXITSTATUS(status) == 0){
                        return true;
                    }
                    else{
                        return false;
                    }
                }
                // while(wait(&status) != pid)
                // ;
            }
            return false;
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
    //deletes comments
    if(commandLine.find("#") != string::npos){
        int location = commandLine.find("#");
        commandLine.erase(location, 999);
    }
    //top of the tree to be executed
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
