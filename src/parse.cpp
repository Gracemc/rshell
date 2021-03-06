#include <parse.hpp>
#include <Command.hpp>
#include <Executable.hpp>
#include <Connector.hpp>

#include <stack>
#include <queue>
#include <string>
#include <vector>

#include <boost/tokenizer.hpp>

using std::vector;
using std::string;
using std::stack;
using std::queue;

bool isOperator(const string &token)
{
	return token == "&&" || token == "||" || token == ";" || token == ">" || token == ">>" || token == "<" || token == "|";
}

vector<string> getCommand(queue<string> &q)
{
	vector<string> vec;
	if (q.front() == "#")
	{
		q.pop();
		while (!q.empty() && q.front() != "#" && !isOperator(q.front()))
		{
			vec.push_back(q.front());
			q.pop();
		}
	}
	else
	{
		vec.push_back(q.front());
		q.pop();
	}
	return vec;
}

Command * parse(const string &command)
{
	Command::uneven_flag = false;
	// delete the command after the comment symbol("#")
	string cmd = command.substr(0, command.find("#"));
    
	// seperate the command by space and connector
	boost::char_separator<char> sep(" ", ";()");
	boost::tokenizer<boost::char_separator<char>> tok(command, sep);

	// convert from infix expression to postfix expression
	queue<std::string> postfix;
	stack<std::string> s;
	bool flag = true;
	// push all the executable into the queue
	for (auto beg = tok.begin(); beg != tok.end(); ++beg)
	{
		if (isOperator(*beg))
		{
			flag = true;
			while (!s.empty() && s.top() != "(")
			{
				postfix.push(s.top());
				s.pop();
			}
			s.push(*beg);
		}
		else if (*beg == "(")
		{
			flag = true;
			s.push(*beg);
		}
		else if (*beg == ")")
		{
			flag = true;
			while (!s.empty() && s.top() != "(")
			{
				postfix.push(s.top());
				s.pop();
			}
			if (!s.empty() && s.top() == "(")
				s.pop();
		}
		else
		{
			if (flag)
				postfix.push("#");
			postfix.push(*beg);
			flag = false;
		}
	}
	// pop the operator
	while (!s.empty())
	{
		if (s.top() == "(")
			Command::uneven_flag = true;
		postfix.push(s.top());
		s.pop();
	}

	// build the Command tree from the postfix expression
	stack<Command*> tree;
	while (!postfix.empty())
	{
		if (isOperator(postfix.front()))
		{
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
		else
		{
			auto c = getCommand(postfix);
			auto t = new Executable(c);
			tree.push(t);
		}                
	}
	return tree.top();
}
