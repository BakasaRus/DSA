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

vector<int> Knuth_Morris_Pratt(string &P, string &T)
{
	int PL = P.length(), TL = T.length();
	vector<int> Res;
	vector<int> Prefix = PrefixFunction(P + "#" + T);
	for (int i = 0; i < TL; ++i)
		if (Prefix[PL + i + 1] == PL)
			Res.push_back(i - PL + 2);
	return Res;
}

int main()
{
	ifstream fin("search2.in");
	ofstream fout("search2.out");
	string T, P;
	fin >> P >> T;
	vector<int> Res = Knuth_Morris_Pratt(P, T);
	fout << Res.size() << endl;
	for (int i = 0; i < Res.size(); ++i)
		fout << Res[i] << " ";
	return 0;
}