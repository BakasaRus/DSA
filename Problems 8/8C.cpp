#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> PrefixFunction(string &T)
{
	vector<int> Res;
	Res.push_back(0);
	for (int i = 1; i < T.length(); ++i)
	{
		int k = Res[i - 1];
		while (k > 0 && T[i] != T[k])
			k = Res[k - 1];
		if (T[i] == T[k])
			++k;
		Res.push_back(k);
	}
	return Res;
}
int main()
{
	ifstream fin("prefix.in");
	ofstream fout("prefix.out");
	string S;
	fin >> S;
	vector<int> Res = PrefixFunction(S);
	for (int i = 0; i < Res.size(); ++i)
		fout << Res[i] << " ";
	return 0;
}