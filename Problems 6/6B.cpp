#include <fstream>

using namespace std;

int V[100][100];

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int N;
	fin >> N;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			fin >> V[i][j];
	for (int i = 0; i < N; ++i)
		for (int j = i; j < N; ++j)
			if (i == j && V[i][j] == 1 || V[i][j] != V[j][i])
			{
				fout << "NO";
				return 0;
			}
	fout << "YES";
	return 0;
}