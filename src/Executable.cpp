#include <Executable.hpp>

#include <iostream>
#include <cstring>
#include <cstdio>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <sys/stat.h>
#include <unistd.h>

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
    struct stat fileStat;
     
    if (exit_flag)
        return 0;
    if (argv[0] == "exit") 
        exit_flag = true;
    else if (argv[0] == "cprompt") 
        prompt_symbol = argv[1];
    else if (argv[0] == "help") {
        cout << "----------------------------------- built-in command: ------------------------------------" << endl;
        cout << "----------------------------- 1. write 'exit' to exit shell ------------------------------" << endl;
        cout << "-------------- 2. write 'cprompt' with an argument to create prompt symbol ---------------" << endl;
        cout << "------------------------------------------------------------------------------------------" << endl;
        cout << "----------------------------------- external command: ------------------------------------" << endl;
        cout << "--------------- 1. write other commands(the same as the commands in bash) ----------------" << endl;
        cout << "------- 2. write 'test'/'[]' with -e/-f/-d and your filepath to set a test command -------" << endl;
        cout << "-------    a) -e checks if the file/directory exists -------------------------------------" << endl;
        cout << "-------    b) -f checks if the file/directory exists and is a regular file ---------------" << endl;
        cout << "-------    c) -d checks if the file/directory exists and is a directory ------------------" << endl;
    }
    else {
        pid_t pid;
        bool isBrackets = false;
        bool matchBrackets = true;
        bool mError = false;
        
        pid = fork();
        
        if (pid == 0) {
            // char *cmd[argv.size() + 1]; // maybe cause error: ISO C++ forbids variable length array 'xxx'
            char* cmd[MAXSIZE];
            
            for (size_t t = 0; t < argv.size(); ++t)
                cmd[t] = const_cast<char*>(argv[t].c_str());
            cmd[argv.size()] = NULL;
            
            if (strcmp(cmd[0], "test") == 0 || strcmp(cmd[0], "[") == 0 ) {
                if (strcmp(cmd[0], "[") == 0)
                    isBrackets = true;
                for (unsigned i = 1; i < argv.size()-1; ++i) {
                    if (strcmp(cmd[i], "]") == 0) {
                        matchBrackets = false;
                    }
                    if (strcmp(cmd[i], "[") == 0) {
                        cout << "ERROR: too many square brackets." << endl;
                        mError = true;
                        matchBrackets = false;
                    }
                }
                if (!isBrackets || (isBrackets && strcmp(cmd[argv.size()-1], "]") == 0 && matchBrackets)) {
                    if (strcmp(cmd[1], "-d") == 0) {
                        if(stat(cmd[2], &fileStat) == -1)
                            perror("stat");
                        else {
                            if (S_ISDIR(fileStat.st_mode)) {
                                cout << "(True)" << endl;
                                return 0;
                            }
                            else {
                                cout << "(False)" << endl;
                                return 1;
                            }
                        }
                    }
                    else if (strcmp(cmd[1], "-f") == 0) {
                        if(stat(cmd[2], &fileStat) == -1) 
                            perror("stat");
                        else {
                            if (S_ISREG(fileStat.st_mode)) {
                                cout << "(True)" << endl;
                                return 0;
                            }
                            else {
                                cout << "(False)" << endl;
                                return 1;
                            }
                        }
                    }
                    else if (strcmp(cmd[1], "-e") == 0) {
                        if(stat(cmd[2], &fileStat) == -1) {
                            cout << "(False)" << endl;
                            return 1;
                        }
                        else {
                            cout << "(True)" << endl;
                            return 0;
                        }
                    }
                    else {
                        if(stat(cmd[1], &fileStat) == -1) {
                            cout << "(False)" << endl;
                            return 1;
                        }
                        else {
                            cout << "(True)" << endl;
                            return 0;
                        }
                    }
                }
                else if (!mError)
                    cout << "ERROR: Uneven amount of square brackets." << endl;
                else ;
            }
            else {
                execvp(cmd[0], cmd);
                if(execvp(cmd[0], cmd) == -1) {
                    perror("COMMAND ERROR");   
                }
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
    
