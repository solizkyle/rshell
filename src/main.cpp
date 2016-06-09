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
#include <sys/stat.h>
#include <sys/wait.h>
#include <stack>
#include <algorithm>
#include <fcntl.h>
#include <math.h>
using namespace std;

//TODO:
//  Finish writing functionality
//  Add testcases
//  Merge the branches and add the "hw4" tag
//  Submit to iLearn

// might have to use for loop in command execute to chain redirections


class Shell{
    public:
        Shell* first;
        Shell* second;
        Shell(){};
        virtual bool execute() = 0;
        virtual string retName() = 0;
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
        string retName(){
            return "";
        }
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
        string retName(){
            return "";
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
        string retName(){
            return "";
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
        string retName(){
            return "";
        }
};

class Par : public Connector{
    public:
        Par() : Connector (){};
        bool execute(){
            return first->execute();
        }
        string retName(){
            return "";
        }
};

class Redir : public Connector{
    //takes output from (left) and overwrites the file on (right)
    public:
        Redir() : Connector(){};
        bool execute(){
            
            //string fileName = "example.txt";
            char file[100];
            strcpy(file, second->retName().c_str());
            int pFile;
            if((pFile = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP)) == -1){
    				perror("Redir Error: Could not open file");
    				return false;
    				// return false; ??? instead
    		}
            int saveStdout = dup(1);
            dup2(pFile, 1);
            first->execute();
            dup2(saveStdout, 1);
            return true;
            
            // int fd_p2c[2];
            // int fd_c2p[2];
            // //sets up both pipes
            // if(pipe(fd_c2p) != 0 || pipe(fd_p2c) != 0){
            //     perror("PIPE FAIL");
            //     exit(EXIT_FAILURE);
            // }
            // //sets output to pipe input
            // dup2(fd_p2c[1], 1);
            // //runs the left command
            // first->execute();
            // //pipe should be full now
            // //sets input to pipe output
            // dup2(fd_p2c[0], 0);
            
            //sets up to execute the left command
            // string left = first->cmd;
            // string outputFile = second->cmd;
            // cout << "first: " << left << endl;
            // cout << "second: " << outputFile << endl;
            // vector<string> arg = first->args;
            // int size = arg.size() + 2;
            // char ** argv = new char*[arg.size() + 2];
            // char *tempcmd = new char[left.size()];
            // strcpy(tempcmd, left.c_str());
            // argv[0] = tempcmd;
            // for(unsigned i = 0; i < arg.size(); ++i){
            //     char *temparg = new char[arg.at(i).size()];
            //     strcpy(temparg, arg.at(i).c_str());
            //     argv[i + 1] = temparg;
            // }
            // argv[size - 1] = NULL;
            // int fd_p2c[2]; //pipe to child
            // int fd_c2p[2]; //child to pipe
            // pid_t pid;
            // if(pipe(fd_p2c) != 0 || pipe(fd_c2p) != 0){
            //     perror("Piping error");
            //     exit(EXIT_FAILURE);
            // }
            // if((pid = fork()) < 0){ //if fork() failed
            //     perror("Fork failed");
            //     return false;
            // }
            // else if(pid == 0){ //if this is the child process
            //     //do stuff
            //     // if(dup2(fd_p2c[0], 0) != 0 || close(fd_p2c[0]) != 0 || close(fd_p2c[1]) != 0){
            //     //     //sets read end of pipe to standard input (fd_p2c[0])
            //     //     perror("CHILD: input setup failed");
            //     //     exit(EXIT_FAILURE);
            //     // }
            //     if(dup2(fd_c2p[1], 1) != 1 || close(fd_c2p[1]) != 0 || close(fd_c2p[0]) != 0){
            //         //sets write end of pipe to standard output (fd_c2p[1])
            //         perror("PARENT: output setup failed");
            //         exit(EXIT_FAILURE);
            //     }
            //     if(execvp(argv[0], argv) < 0){   //executes the command: if it fails, returns -1, else continue
            //         perror("( ͡° ͜ʖ ͡°)  INVALID COMMAND");
            //         exit(EXIT_FAILURE);
            //     }
                
            // }
            // else{ //parent process
            //     if(dup2(fd_p2c[0], 0) != 0 || close(fd_p2c[0]) != 0 || close(fd_p2c[1]) != 0){
            //         //sets read end of pipe to standard input (fd_p2c[0])
            //         perror("CHILD: input setup failed");
            //         exit(EXIT_FAILURE);
            //     }
            //     int status;
            //     waitpid(pid, &status, WUNTRACED | WCONTINUED);
            //     if(WIFEXITED(status)){
            //         if(WEXITSTATUS(status) == 0){
            //             //sets up everything to run second command
            //             cout << "this is from the pipe" << fd_p2c[0] << endl;
                        
            //             return true;
            //         }
            //         else{
            //             return false;
            //         }
            //     }
            // }
        }
        string retName(){
            return "";
        }
};

class Input : public Connector{
    //takes output from (left) and overwrites the file on (right)
    public:
        Input() : Connector (){};
        bool execute(){
            
            char file[100];
			strcpy(file, second->retName().c_str());
            int pFile;
			if((pFile = open(file, O_RDONLY )) == -1) {
				perror("Input Redirection Error: Could not open file");
				return false;
			}
			
			int saveSTDin = dup(0);
			dup2(pFile, 0);
			first->execute();
			dup2(saveSTDin, 0);
            return true;
        }
        string retName(){
            return "";
        }
};

class Append: public Connector{
    //takes output from (left) and appends to file on (right)
    public: 
        Append() : Connector(){};
        bool execute(){
            // string fileName = "example.txt";
            char file[100];
            strcpy(file, second->retName().c_str());
            int pFile;
            if((pFile = open(file, O_RDWR | O_APPEND | O_CREAT , S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP )) == -1){
    				perror("Append Error: Could not open file");
    				return false;
    				// return false; ??? instead
    		}
            int saveStdout = dup(1);
            dup2(pFile, 1);
            first->execute();
            dup2(saveStdout, 1);
            
            return true;
        }
        string retName(){
            return "";
        }
};

class Pipe: public Connector{
    public: 
        Pipe() : Connector() {};
        bool execute(){
            //create a pipe
            int fd[2];
            pipe(fd);
            //set std out to pipe in
            int saveStdout = dup(1);
            dup2(fd[1], 1);
            //execute first
            first->execute();
            close(fd[1]);
            int saveStdin = dup(0);
            //set std in to pipe out
            dup2(fd[0], 0);
            //reset std out to normal
            dup2(saveStdout, 1);
            //execute second
            second->execute();
            close(fd[0]);
            dup2(saveStdin, 0);
            return true;
        }
        string retName(){
            return "";
        }
};

class Command : public Shell{
    public:
        string cmd;
        vector<string> args;
        Command() : Shell(){};
        Command(string c, vector<string> a) : Shell(), cmd(c), args(a) {};
        string retName(){
            return cmd;
        }
        bool execute(){
            //cout << "cmd: " << cmd << endl;
            if(cmd == "exit"){
                exit(0);
            }
            
            string flag;
            string directory;
            if(cmd.at(0) == '[' || cmd == "test"){
                //do the test command stuff
                if(args.size() == 1){
                    flag = "-e";
                    directory = args.at(0);
                }
                else{
                    flag = args.at(0);
                    directory = args.at(1);
                }
                struct stat sb;
                //const char* dir = new char[directory.size() + 1];
                char temp[1024];
                strcpy(temp, directory.c_str());
                const char* dir = temp;
                if(stat(dir, &sb) == -1){
                    cout << "(False)" << endl;
                    return false;
                }
                if(flag == "-f"){
                    if(S_ISREG(sb.st_mode)){
                        cout << "(True)" << endl;
                        return true;
                    }
                    cout << "(False)" << endl;
                    return false;
                }
                else if(flag == "-d"){
                    if(S_ISDIR(sb.st_mode)){
                        cout << "(True)" << endl;
                        return true;
                    }
                    cout << "(False)" << endl;
                    return false;
                }
                cout << "(True)" << endl;
                return true;
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
                    perror("( ͡° ͜ʖ ͡°)  INVALID COMMAND");
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

Shell* parse(string commandLine){
    //deletes comments
    if(commandLine.find("#") != string::npos){
        int location = commandLine.find("#");
        commandLine.erase(location, 999);
    }
    //top of the tree to be executed
    Shell* top = NULL;

    for(unsigned i = 0; i < commandLine.size(); ++i){
        string temp;
        //stack
        //bool closed = true;
        // checks for parenthesis & adjusts stack
        if(commandLine.at(i) == ';' /* && closed == true */){
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
                connect->first = parse(temp);
            }
            else{
                Shell* connect = new Semi;
                connect->first = top;
                top->second = parse(temp);
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
                    connect->first = parse(temp);
                }
                else{
                    Shell* connect = new Bars;
                    connect->first = top;
                    top->second = parse(temp);
                    top = connect;
                }
            }
            else{
            //make substr
            temp = commandLine.substr(0, i); // didn't include actual character
            //delete what we took
            commandLine.erase(0, i + 1);
            // reset i
            i = 0;
            //make pipe command
            if(top == NULL){
                Shell* connect = new Pipe;
                top = connect;
                connect->first = parse(temp);
            }
            else{
                Shell* connect = new Pipe;
                connect->first = top;
                top->second = parse(temp);
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
                    connect->first = parse(temp);
                }
                else{
                    Shell* connect = new Amp;
                    connect->first = top;
                    top->second = parse(temp);
                    top = connect;
                }
            }
        }
        else if(commandLine.at(i) == '('){
            if(commandLine.find('(') == string::npos){
                cout << "INVALID COMMAND: No matching )" << endl;
                exit(0);
            } 
            stack<int> parenthesis;
            int endLocation = 0;
            //goes through commandLine character by character
            parenthesis.push(i);
            for(unsigned j = i + 1; !parenthesis.empty(); ++j){
                if(commandLine.at(j) == '('){
                    parenthesis.push(j);
                }
                else if(commandLine.at(j) == ')'){
                    parenthesis.pop();
                }
                endLocation = j;
            }
            temp = commandLine.substr(i + 1, endLocation - i - 1);
            commandLine.erase(i, endLocation - i + 1);
            //everything from above only deals with parenthesis
            //below is the same logic from every other connector
            if(top == NULL){
                Shell* connect = new Par;
                top = connect;
                connect->first = parse(temp);
            }
            else{
                Shell* connect = new Par;
                connect->first = parse(temp);
                top->second = connect;
            }
        }
        else if(commandLine.at(i) == '>'){
            if(commandLine.at(i + 1) == '>'){
                //make substr
                temp = commandLine.substr(0, i);
                //delete what we took
                commandLine.erase(0, i + 2);//make redir command
                // // get file name
                // stringstream ss (commandLine);
                // string redirFile;
                // ss >> redirFile;
                // commandLine = ss.str();
                i = 0;
                if(top == NULL){
                    Shell* connect = new Append;
                    top = connect;
                    connect->first = parse(temp);
                }
                else{
                    // Shell* connect = new Append;
                    // connect->first = stringToCommand(temp);
                    // top->second = connect;
                    
                    Shell* connect = new Append;
                    connect->first = top;
                    top->second = parse(temp);
                    top = connect;
                }
            }
            else{
                //make substr
                temp = commandLine.substr(0, i); // didn't include actual character
                //delete what we took
                commandLine.erase(0, i + 1);
                // get file name
                stringstream ss (commandLine);
                string redirFile;
                ss >> redirFile;
                commandLine = ss.str();
                i = 0;
                //make append command
                if(top == NULL){
                    Shell* connect = new Redir;
                    top = connect;
                    connect->first = parse(temp);
                }
                else{
                    Shell* connect = new Redir;
                    connect->first = top;
                    top->second = parse(temp);
                    top = connect;
                }
            }
        }
        else if(commandLine.at(i) == '<'){
            //main substr
            temp = commandLine.substr(0, i); // didn't include actual character
            //delete what we took
            commandLine.erase(0, i + 1);
            // reset i
            i = 0;
            //make input command
            if(top == NULL){
                Shell* connect = new Input;
                top = connect;
                connect->first = parse(temp);
            }
            else{
                // Shell* connect = new Input;
                // connect->first = parse(temp);
                // top->second = connect;
            
                Shell* connect = new Input;
                connect->first = top;
                top->second = parse(temp);
                top = connect;
            }
        }
    }
    if(commandLine.size() == 1){
        return top;
    }
    string temp = commandLine;
    if(top == NULL){
        top = stringToCommand(temp);
    }
    else{
        top->second = stringToCommand(temp);
    }
    //top->execute();
    return top;
}

//extra credit prompt
void getUser(string &prompt){
    char* user = getlogin();
    if(user == NULL){
        cout << "Can't get login" << endl;
        return;
    }
    char host[1024];
    gethostname(host, 1023);
    prompt = prompt + user + '@' + host;
}

int main() {
    string commandLine;
    string prompt;
    getUser(prompt);
    prompt = prompt + "$";
    while(cout << prompt && getline(cin, commandLine) && commandLine != "exit"){
        Shell* tree = parse(commandLine);
        tree->execute();
    }
    return 0;
}
