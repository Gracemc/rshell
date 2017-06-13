#include <Connector.hpp>
#include <parse.hpp>
#include <Executable.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

using std::vector;
using std::string;
using std::cout;
using std::endl;

#define MAX 100 

Connector::Connector(vector<string> &argv, Command *l, Command *r) : Command(argv), lchild(l), rchild(r) { }

int Connector::exec() const {
    int status = 0;
    
    if (exit_flag)
        return 0;
    
    if (argv[0] == ";") {
        lchild->exec();
        rchild->exec();
    }
    else if (argv[0] == "&&") {
        if (lchild->exec() == 0)
            rchild->exec();
    }
    else if (argv[0] == "||") {
        if (lchild->exec() != 0)
            rchild->exec();
    }
    else if (argv[0] == ">") {
        int stdout_copy_fd = dup(STDOUT_FILENO);
        const char* fileName = rchild->get();
        int file_fd;
        if ((file_fd = open(fileName, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == -1) { //O_CREAT create a file if file not exist
            perror("OPEN FILE ERROR");
        }
        
        dup2(file_fd, STDOUT_FILENO);
        lchild->exec();

        dup2(stdout_copy_fd, STDOUT_FILENO);
    }
    else if (argv[0] == ">>") {
        int stdout_copy_fd = dup(STDOUT_FILENO);
        const char* fileName = rchild->get();
        int file_fd;
        if ((file_fd = open(fileName, O_RDWR|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == -1) { //O_APPEND append to file 
            perror("OPEN FILE ERROR");
        }
        
        dup2(file_fd, STDOUT_FILENO);
        lchild->exec();

        dup2(stdout_copy_fd, STDOUT_FILENO);
    }
    
    else if (argv[0] == "<") {
        char buf[MAX];
        int stdin_copy_fd = dup(STDIN_FILENO);
        const char* fileName = rchild->get();
        int file_fd;
        file_fd = open(fileName, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
        int file_read;
        if ((file_read = read(file_fd, buf, MAX)) == -1) {
            perror("READ FILE ERROR");
        }
        dup2(file_read, STDIN_FILENO);
        
        string newCmd;
        const char* newCommand = lchild->get();
        newCmd.append(newCommand);
        newCmd.append(" ");
        newCmd.append(buf);
        const string Cmd = newCmd;
        
        Command* newLchild = parse(Cmd);
        newLchild->exec();

        dup2(stdin_copy_fd, STDIN_FILENO);
    }
    
    else if (argv[0] == "|") {
        
    }
    
    else ;
    
    return status;
}

Connector::~Connector() {
    delete lchild;
    delete rchild;
}

void Connector::print() const {
    lchild->print();
    cout << " " << argv[0] << " ";
    rchild->print();
}

const char* Connector::get() const{
    const char* fileName = argv[0].c_str();
    return fileName;
}
    
