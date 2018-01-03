#include <fstream>
#include <vector>

using namespace std;

enum VColor { White, Gray, Black };

bool Cycles = false;

struct Vertex
{
	vector<int> Neighbours;
	VColor Color = White;
};

void DFS_Visit(vector<Vertex> &V, int U, vector<int> &Res)
{
	if (V[U].Color == Black) return;
	if (V[U].Color == Gray) Cycles = true;
	if (Cycles) return;
	V[U].Color = Gray;
	for (int i = 0; i < V[U].Neighbours.size(); ++i)
	{
		DFS_Visit(V, V[U].Neighbours[i], Res);
	}
	V[U].Color = Black;
	Res.push_back(U);
}

void DFS(vector<Vertex> &V, vector<int> &Res)
{
	for (int i = 0; i < V.size(); ++i)
		if (V[i].Color == White)
			DFS_Visit(V, i, Res);
}

int main()
{
	ifstream fin("topsort.in");
	ofstream fout("topsort.out");
	int N, M, S, E;
	fin >> N >> M;
	vector<Vertex> V(N);
	vector<int> Res;
	for (int i = 0; i < M; ++i)
	{
		fin >> S >> E;
		V[S - 1].Neighbours.push_back(E - 1);
	}
	DFS(V, Res);
	if (Cycles)
		fout << "-1";
	else
		for (int i = Res.size() - 1; i >= 0; --i)
			fout << Res[i] + 1 << " ";
	return 0;
}