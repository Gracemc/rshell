# rshell
rshell is a shell written in C++. It perform the following steps:
1. Print a command prompt, default is `*_*` (so cute!!!).
2. Read in a command on one line. Commands will have the form:

cmd       = executable [ argumentList ] [connector cmd]

connector = `||` or `&&` or `;`

`#` stands for comment, every content after it will be ignored

# built-in command
`exit` for exit

`cprompt <new prompt symbol>` for change the prompt symbol

# bugs
1. `echo "#123"` will be executed as `echo"`
2. When the connector is greater than 2, Segmentation fault will occur.   
e.g.  command:  `ls && echo hi || echo a`  and the result will be  `hi Segmentation fault`
3. As an array size can not be a variable, we define a macro named `MAXSIZE` and set it to 100, but it can still be not big enough to store commands.
