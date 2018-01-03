#include <fstream>

using namespace std;

int V[100][100];

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int N, M, S, E;
	fin >> N >> M;
	for (int i = 0; i < M; ++i)
	{
		fin >> S >> E;
		++V[S - 1][E - 1];
		++V[E - 1][S - 1];
	}
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			if (V[i][j] > 1)
			{
				fout << "YES";
				return 0;
			}
	fout << "NO";
	return 0;
}