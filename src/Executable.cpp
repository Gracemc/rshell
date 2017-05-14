#include <Executable.hpp>

#include <iostream>
#include <cstdio>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::perror;

// may not big enough, cause error
#define MAXSIZE 100 

Executable::Executable(vector<string> &c) : Command(c) { }

int Executable::exec() const
{
    int status = -1;
    
    if (exit_flag)
        return 0;
    if (argv[0] == "exit") 
        exit_flag = true;
    else if (argv[0] == "cprompt") 
        prompt_symbol = argv[1];
    else if (argv[0] == "help") {
        cout << "---------------------------- built-in command: ----------------------------" << endl;
        cout << "---------------------- 1. write 'exit' to exit shell ----------------------" << endl;
        cout << "------- 2. write 'cprompt' with an argument to create prompt symbol -------" << endl;
        cout << "---------------------------------------------------------------------------" << endl;
        cout << "---------------------------- external command: ----------------------------" << endl;
        cout << "---------- write other commands(the same as the commands in bash) ---------" << endl;
    }
    else {
        pid_t pid;
        
        pid = fork();
        
        if (pid == 0) {
            // char *cmd[argv.size() + 1]; // maybe cause error: ISO C++ forbids variable length array 'xxx'
            char* cmd[MAXSIZE];
            
            for (size_t t = 0; t < argv.size(); ++t)
                cmd[t] = const_cast<char*>(argv[t].c_str());
            cmd[argv.size()] = NULL;
            
            execvp(cmd[0], cmd);
            if(execvp(cmd[0], cmd) == -1) {
                perror("COMMAND ERROR");   
            }
        }
        else if (pid == -1) {
            perror("FORK ERROR");
            exit(1);
        }
        else
            waitpid(pid, &status, WUNTRACED);
    }
    return status;
}

void Executable::print() const {
    cout << argv[0];
}
    
