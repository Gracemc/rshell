#ifndef EXECUTABLE_HPP
#define EXECUTABLE_HPP

#include <Command.hpp>

class Executable : public Command {
public:
    Executable(std::vector<std::string> &c);
    void print() const override;
    int  exec() const override;
};

#endif
