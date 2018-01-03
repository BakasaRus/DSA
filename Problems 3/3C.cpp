#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Stack
{
	vector<char> source;

public:
	void push(char v)
	{
		source.push_back(v);
	}
	void pop()
	{
		if (!isEmpty())
			source.pop_back();
	}
	char top()
	{
		if (isEmpty())
			return 0;
		return source.back();
	}
	bool isEmpty()
	{
		return source.size() == 0;
	}
};

bool isCorrect(string s)
{
	Stack stack;
	for (int i = 0; i < s.length(); i++)
		if (s[i] == '(' || s[i] == '[')
			stack.push(s[i]);
		else if (!(s[i] == ')' && stack.top() == '(' || s[i] == ']' && stack.top() == '['))
			return false;
		else
			stack.pop();
	if (stack.isEmpty())
		return true;
	else
		return false;
}

int main()
{
	ifstream fin("brackets.in");
	ofstream fout("brackets.out");
	string test;
	while (fin >> test)
	{
		if (isCorrect(test))
			fout << "YES" << endl;
		else
			fout << "NO" << endl;
	}
	return 0;
}