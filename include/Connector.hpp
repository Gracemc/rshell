#ifndef CONNECTOR_HPP
#define CONNECTOR_HPP

#include <Command.hpp>

class Connector : public Command {
protected:
    Command *lchild;
    Command *rchild;
public:
    Connector(std::vector<std::string> &argv, Command *lchild, Command *rchild);
    int exec() const override;
    void print() const override;
    ~Connector() override;
};

#endif
