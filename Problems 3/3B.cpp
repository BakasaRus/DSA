#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Queue
{
	vector<int> source;

public:
	void push(int v)
	{
		source.push_back(v);
	}
	int pop()
	{
		int v = source.front();
		source.erase(source.begin());
		return v;
	}
};

int main()
{
	ifstream fin("queue.in");
	ofstream fout("queue.out");
	int m;
	fin >> m;
	Queue s;
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