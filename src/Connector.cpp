#include <Connector.hpp>

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

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
    return status;
}

Connector::~Connector() {
    delete lchild;
    delete rchild;
}
