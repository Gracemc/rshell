#include <Command.hpp>
#include <parse.hpp>

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;

int main()
{
    cout << "-----type 'help' for instructions-----" << endl;
    cout << prompt_symbol << " ";

    string command;
    while (getline(cin, command)) {
        
        auto t = parse(command);
        t->exec();
        
        if (exit_flag)
            break;
        
        cout << prompt_symbol << " ";
    }

    return 0;
}
