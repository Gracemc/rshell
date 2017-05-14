#include <rshell.hpp>

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
    cout << Command::prompt_symbol << " ";

    string command;
    while (getline(cin, command)) {
        
        auto t = parse(command);
        t->exec();
        
        if (Command::exit_flag)
            break;
        
        cout << Command::prompt_symbol << " ";
    }

    return 0;
}
