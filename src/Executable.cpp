#include <Executable.hpp>

#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using std::string;
using std::vector;
using std::cout;

#define MAXSIZE 100 //may not big enough, cause error

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
        std::cout << "---------------------------- built-in command: ----------------------------" << std::endl;
        std::cout << "---------------------- 1. write 'exit' to exit shell ----------------------" << std::endl;
        std::cout << "------- 2. write 'cprompt' with an argument to create prompt symbol -------" << std::endl;
        std::cout << "---------------------------------------------------------------------------" << std::endl;
        std::cout << "---------------------------- external command: ----------------------------" << std::endl;
        std::cout << "---------- write other commands(the same as the commands in bash) ---------" << std::endl;
    }
    else {
        pid_t pid;
        
        pid = fork();
        
        if (pid == 0) {
            //char *cmd[argv.size() + 1]; will cause error: ISO C++ forbids variable length array 'xxx'
            char *cmd[MAXSIZE];
            for (auto t = 0; t < argv.size(); ++t)
                cmd[t] = const_cast<char*>(argv[t].c_str());
            cmd[argv.size()] = NULL;
            execvp(cmd[0], cmd);
            if(execvp(cmd[0], cmd) == -1) {
                perror("Error! Invaild command");   
            }
        }
        else
            waitpid(pid, &status, WUNTRACED);
    }
    return status;
}

void Executable::print() const {
    for (auto it = argv.begin(); it != argv.end(); ++it) {
        if (!(it == argv.begin()))
            cout << " ";
        cout << *it;
    }
}
