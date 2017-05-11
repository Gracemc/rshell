#include <Command.hpp>
#include <parse.hpp>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string command;
    cout << "-----type 'help' for instructions-----" << endl;
    do {
        cout << prompt_symbol << " ";
        getline(cin, command);
        auto t = parse(command);
        t->exec();
    } while (!exit_flag);

    return 0;
}
