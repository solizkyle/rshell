#include <iostream>
#include <string>
using namespace std;

//TODO:
//  Create parse function
//  Add execute functionality to both classes
//  Write loop in main function


class Shell{
    virtual bool execute() = 0;
};

class Connector: public Shell{
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

int main() {


    return 0
}
