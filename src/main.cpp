#include <Command.hpp>
#include <iostream>
#include <string>

int main()
{
    std::string command;
    do {
        std::cout << prompt_symbol << " ";
        getline(std::cin, command);
        auto t = parse(command);
        t->exec();
    } while (!exit_flag);
}
