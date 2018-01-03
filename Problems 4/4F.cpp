#include <fstream>
#include <stack>
#include <algorithm>

using namespace std;

class StackMin
{
	stack<pair<int, int>> Src;
public:
	void push(int x)
	{
		int minimum = isEmpty() ? x : min(x, Src.top().second);
		Src.push(make_pair(x, minimum));
	}
	int pop()
	{
		int x = Src.top().first;
		Src.pop();
		return x;
	}
	bool isEmpty()
	{
		return Src.size() == 0;
	}
	int getMin()
	{
		return Src.top().second;
	}
};

class QueueMin
{
	StackMin st1, st2;
public:
	void enqueue(int x)
	{
		st1.push(x);
	}
	int dequeue()
	{
		if (st2.isEmpty())
			while (!st1.isEmpty())
				st2.push(st1.pop());
		return st2.pop();
	}
	int getMin()
	{
		if (st1.isEmpty() || st2.isEmpty())
			return st1.isEmpty() ? st2.getMin() : st1.getMin();
		else
			return min(st1.getMin(), st2.getMin());
	}
};

int main()
{
	ifstream fin("queuemin.in");
	ofstream fout("queuemin.out");
	int M;
	QueueMin QM;
	fin >> M;
	for (int i = 0; i < M; i++)
	{
		char c;
		int x;
		fin >> c;
		if (c == '+')
		{
			fin >> x;
			QM.enqueue(x);
		}
		else if (c == '-')
			QM.dequeue();
		else
			fout << QM.getMin() << endl;
	}
	return 0;
}