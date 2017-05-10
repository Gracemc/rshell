#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>

extern bool exit_flag;
extern std::string prompt_symbol;

class Command {
protected:
    std::vector<std::string> argv;
public:
    Command(std::vector<std::string> &v);
    virtual int exec() const = 0;
    virtual void print() const = 0;
};

Command * parse(const std::string &command);

#endif
