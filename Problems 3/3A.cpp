#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Stack
{
	vector<int> source;

public:
	void push(int v)
	{
		source.push_back(v);
	}
	int pop()
	{
		int v = source.back();
		source.pop_back();
		return v;
	}
};

int main()
{
	ifstream fin("stack.in");
	ofstream fout("stack.out");
	int m;
	fin >> m;
	Stack s;
	for (int i = 0; i < m; i++)
	{
		string command;
		fin >> command;
		if (command == "+")
		{
			int value;
			fin >> value;
			s.push(value);
		}
		else
		{
			fout << s.pop() << endl;
		}
	}
	return 0;
}