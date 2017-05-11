#include <Command.hpp>

#include <vector>
#include <string>

using std::string;
using std::vector;

// global varible definition
bool exit_flag = false;
string prompt_symbol = "*_*";

Command::Command(vector<string> &v) : argv(v) { }
