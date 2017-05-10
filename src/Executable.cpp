#include <Executable.hpp>

#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using std::string;
using std::vector;
using std::cout;

Executable::Executable(vector<string> &c) : Command(c) { }

int Executable::exec() const
{
    int status = -1;
    
    if (exit_flag)
        return 0;
    if (argv[0] == "q")
        exit_flag = true;
    else if (argv[0] == "c")
        prompt_symbol = argv[1];
    else {
        pid_t pid, wpid;
        
        pid = fork();
        
        if (pid == 0) {
            char *cmd[argv.size() + 1];
            for (auto t = 0; t < argv.size(); ++t)
                cmd[t] = const_cast<char*>(argv[t].c_str());
            cmd[argv.size()] = NULL;
            execvp(cmd[0], cmd);
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
