# rshell
rshell is a shell written in C++. It perform the following steps:
1. Print a command prompt, default is `*_*` (so cute!!!).
2. Read in a command on one line. Commands will have the form:

cmd       = executable [ argumentList ] [connector cmd]

connector = `||` or `&&` or `;`

`#` stands for comment, every content after it will be ignored

# built-in command
`q` for exit

`c <new prompt symbol>` for change the prompt symbol

# bugs
1. `echo "#123"` will be executed as `echo"`

