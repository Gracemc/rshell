# rshell

## Basic Usage
rshell is a shell written in C++. It perform the following steps:
1. Print a command prompt, default is `$` (so cute!!!).
2. Read in a command on one line. Commands will have the form:

cmd       = executable [ argumentList ] [connector cmd]

connector = `||` or `&&` or `;`

`#` stands for comment, every content after it will be ignored

## built-in command
`exit` for exit

`cprompt <new prompt symbol>` for change the prompt symbol

`test/[]` for test statement
`-e` checks if the file/directory exists
`-f` checks if the file/directory exists
`-d` checks if the file/directory exists

## bugs
1. `echo "#123"` will be executed as `echo"`, because of stupid comment(just erase all the content after comment).

