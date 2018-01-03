#include<fstream>
#include<string>
#include<vector>

using namespace std;

int main()
{
	ifstream fin("search1.in");
	ofstream fout("search1.out");
	string P, T;
	fin >> P >> T;
	if (P.length() > T.length())
	{
		fout << "0" << endl;
		return 0;
	}
	vector<int> Res;
	for (int i = 0; i < T.length() - P.length() + 1; ++i)
	{
		int j;
		for (j = 0; j < P.length(); ++j)
			if (P[j] != T[i + j])
				break;
		if (j == P.length())
			Res.push_back(i + 1);
	}
	fout << Res.size() << endl;
	for (int i = 0; i < Res.size(); ++i)
		fout << Res[i] << " ";

	return 0;
}