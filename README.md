# Rshell
_______
### Authors
Jake Morales, Kyle Soliz
___
### Synopsis
**Rshell** is command shell written in C++. Rshell will run any command in */bin* with an additional command, *"exit"*. *"exit"* quits the **Rshell** program. Multiple commands on one line may be executed at the same time if they are seperated by **";"**, **"||"** and/or **"&&"**. **";"** will executed the next command regardless if the previous commands fails or not. **"||"** executes the next command if the previous one fails. **"&&"** executes the next command if the previous one succeeds.
___
### Execution
In the rshell directory, run *make*. This creates an executeable. Then, run *./rshell* to execute.
___
### Testing
In the *tests* folder, there are multiple bash scripts for testing various cases. Run *"./_test_.sh"*. It will automatically compile rshell in the test folder, run the script, and delete the rshell it made. 
___
### License
Read the LICENSE file for more information about the BDS3 license.
___
### Known Bugs
1. Prints the prompt twice if user inputs a bad command.
2. Both the getLogin() and the test functions do not work on Clound9
3. Using the test command causes the prompt to bug out and print multiple times