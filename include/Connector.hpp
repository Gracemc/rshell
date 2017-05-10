#ifndef CONNECTOR_HPP
#define CONNECTOR_HPP

#include <Command.hpp>

class Connector : public Command {
protected:
    Command *lchild;
    Command *rchild;
public:
    Connector(std::vector<std::string> &argv, Command *lchild, Command *rchild);
    void print() const override;
    int exec() const override;
};

#endif
