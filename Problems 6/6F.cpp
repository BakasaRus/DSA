#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <iostream>

using namespace std;

enum VColor { White, Gray, Black };

struct Vertex
{
	vector<int> Neighbours;
	VColor Color = White;
	int Parent = -1;
	int Distance = 0;
};

void BFS(vector<Vertex> &G, int Start)
{
	G[Start].Color = Gray;
	queue<int> Q;
	Q.push(Start);
	while (!Q.empty())
	{
		int U = Q.front();
		Q.pop();
		for (int i = 0; i < G[U].Neighbours.size(); ++i)
			if (G[G[U].Neighbours[i]].Color == White)
			{
				G[G[U].Neighbours[i]].Color = Gray;
				G[G[U].Neighbours[i]].Distance = G[U].Distance + 1;
				G[G[U].Neighbours[i]].Parent = U;
				Q.push(G[U].Neighbours[i]);
			}
		G[U].Color = Black;
	}
}

int GenVerNum(int i, int j, int m)
{
	return ((i - 1) * m + (j - 1));
}

string RecoverPath(vector<Vertex> &G, int S, int T)
{
	string Res;
	int Cur = T;
	while (Cur != S)
	{
		if (G[Cur].Parent - Cur == -1)
			Res = "R" + Res;
		if (G[Cur].Parent - Cur == 1)
			Res = "L" + Res;
		if (G[Cur].Parent - Cur < -1)
			Res = "D" + Res;
		if (G[Cur].Parent - Cur > 1)
			Res = "U" + Res;
		Cur = G[Cur].Parent;
	}
	return Res;
}

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int N, M, S, T;
	fin >> N >> M;
	vector<Vertex> G;
	char L[102][102];

	for (int i = 0; i <= N + 1; ++i) L[i][0] = L[i][M + 1] = '#';
	for (int i = 0; i <= M + 1; ++i) L[0][i] = L[N + 1][i] = '#';
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= M; ++j)
			fin >> L[i][j];

	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= M; ++j)
		{
			Vertex Ver;
			if (L[i][j] == '#') Ver.Color = Black;
			if (L[i][j] == 'S') S = GenVerNum(i, j, M);
			if (L[i][j] == 'T') T = GenVerNum(i, j, M);
			//cerr << "Neighbours of " << GenVerNum(i, j, M) << " are: ";
			if (L[i + 1][j] != '#')
			{
				Ver.Neighbours.push_back(GenVerNum(i + 1, j, M));
				//cerr << GenVerNum(i + 1, j, M) << " ";
			}
			if (L[i - 1][j] != '#')
			{
				Ver.Neighbours.push_back(GenVerNum(i - 1, j, M));
				//cerr << GenVerNum(i - 1, j, M) << " ";
			}
			if (L[i][j + 1] != '#')
			{
				Ver.Neighbours.push_back(GenVerNum(i, j + 1, M));
				//cerr << GenVerNum(i, j + 1, M) << " ";
			}
			if (L[i][j - 1] != '#')
			{
				Ver.Neighbours.push_back(GenVerNum(i, j - 1, M));
				//cerr << GenVerNum(i, j - 1, M) << " ";
			}
			cerr << "\n";
			G.push_back(Ver);
		}
	BFS(G, S);
	if (G[T].Distance == 0)
		fout << -1;
	else
		fout << G[T].Distance << "\n" << RecoverPath(G, S, T);
	return 0;
}