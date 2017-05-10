#include <Command.hpp>
#include <Executable.hpp>
#include <Connector.hpp>

#include <stack>
#include <queue>
#include <algorithm>

#include <boost/tokenizer.hpp>

using std::string;
using std::vector;
using std::queue;
using std::queue;
using std::stack;
using std::size_t;

bool exit_flag = false;
string prompt_symbol = "*_*";

Command::Command(vector<string> &v) : argv(v) { }

bool isOperator(const string &token)
{
    return token == "&&" || token == "||" || token == ";";
}

int priority(const string &op)
{
    if (op == ";")
        return 3;
    else if (op == "&&")
        return 2;
    else if (op == "||")
        return 1;
    else
        return 0;
}

vector<string> getCommand(queue<string> &q)
{
    vector<string> vec;
    if (q.front() == "#")
        q.pop();
    while (!q.empty() && q.front() != "#" && !isOperator(q.front())) {
        vec.push_back(q.front());
        q.pop();
    }
    return vec;
}

Command * parse(const string &command)
{
    // delete the command after the comment symbol("#")
    string cmd = command.substr(0, command.find("#"));
    
    // seperate the command by space and connector
    boost::char_separator<char> sep(" ", ";");
    boost::tokenizer<boost::char_separator<char>> tok(command, sep);

    // convert from infix expression to postfix expression
    queue<std::string> postfix;
    stack<std::string> s;
    for (auto beg = tok.begin(); beg != tok.end(); ++beg) {
        if (isOperator(*beg)) {
            postfix.push("#");                                              // each executable is end with a #
            while (!s.empty()
                   && priority(*beg) <= priority(s.top())
                ) {
                postfix.push(s.top());
                s.pop();
            }
            s.push(*beg);
        }
        else
            postfix.push(*beg);
    }
    // pop the rest
    while (!s.empty()) {
        postfix.push(s.top());
        s.pop();
    }

    // build the Command tree from the postfix expression
    stack<Command*> tree;
    while (!postfix.empty()) {
        if (isOperator(postfix.front())) {
            auto r = tree.top();
            tree.pop();
            auto l = tree.top();
            tree.pop();
            vector<string> vec;
            vec.push_back(postfix.front());
            auto t = new Connector(vec, l, r);
            tree.push(t);
            postfix.pop();
        }
        else {
            auto c = getCommand(postfix);
            auto t = new Executable(c);
            tree.push(t);
        }                
    }
    return tree.top();
}


