#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>

class Command {
public:
    static bool exit_flag;
    static std::string prompt_symbol;
protected:
    std::vector<std::string> argv;
public:
    Command(std::vector<std::string> &v);
    virtual int exec() const = 0;
    virtual void print() const = 0;
    virtual ~Command() = default;
};

#endif
