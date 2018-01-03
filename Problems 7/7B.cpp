#include<fstream>
#include<vector>

using namespace std;

int G[200][200];

int main()
{
	ifstream fin("pathsg.in");
	ofstream fout("pathsg.out");
	int N, M, X, Y, W;
	fin >> N >> M;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			G[i][j] = 10001;
	for (int i = 0; i < M; ++i)
	{
		fin >> X >> Y >> W;
		G[X-1][Y-1] = W;
	}
	for (int k = 0; k < N; ++k)
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				if (G[i][j] > G[i][k] + G[k][j] && (i != j))
					G[i][j] = G[i][k] + G[k][j];
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
			fout << (G[i][j] != 10001 ? G[i][j] : 0) << " ";
		fout << "\n";
	}
	return 0;
}