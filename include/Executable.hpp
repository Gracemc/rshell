#ifndef EXECUTABLE_HPP
#define EXECUTABLE_HPP

#include <Command.hpp>

class Executable : public Command {
public:
    Executable(std::vector<std::string> &c);
    int  exec() const override;
    void print() const override;
    const char* get() const override;
};

#endif
