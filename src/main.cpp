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
	cout << Command::prompt_symbol << " ";

	string command;
	while (getline(cin, command))
	{
        
		auto t = parse(command);
		
		if (Command::uneven_flag)
			cout << "ERROR: Uneven amount of parentheses." << endl;
		else
			t->exec();
        
		if (Command::exit_flag)
			break;
        
		cout << Command::prompt_symbol << " ";
	}

	return 0;
}
