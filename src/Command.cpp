#include <Command.hpp>

using std::string;
using std::vector;

// static data member definition
bool Command::exit_flag = false;
string Command::prompt_symbol = "*_*";
bool Command::uneven_flag = false;

Command::Command(vector<string> &v) : argv(v) { }
