#include <fstream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
class Stack
{
	vector<T> source;

public:
	void push(T v)
	{
		source.push_back(v);
	}
	T pop()
	{
		int v = source.back();
		source.pop_back();
		return v;
	}
};

int main()
{
	Stack<int> s;
	ifstream fin("postfix.in");
	ofstream fout("postfix.out");
	string t;
	while (fin >> t)
	{
		int res;
		if (t[0] - 48 >= 0)
			s.push(t[0] - 48);
		else
		{
			int v1 = s.pop(), v2 = s.pop();
			switch (t[0])
			{
			case '+':
				res = v2 + v1;
				s.push(res);
				break;
			case '-':
				res = v2 - v1;
				s.push(res);
				break;
			case '*':
				res = v2 * v1;
				s.push(res);
				break;
			case '/':
				res = v2 / v1;
				s.push(res);
				break;
			}

		}
	}
	fout << s.pop();
	return 0;
}