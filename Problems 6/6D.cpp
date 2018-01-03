#include <fstream>
#include <vector>

using namespace std;

enum VColor { White, Gray, Black };

struct Vertex
{
	vector<int> Neighbours;
	VColor Color = White;
	int ComponentNumber = 0;
};

void DFS_Visit(vector<Vertex> &V, int U, int CompNum)
{
	V[U].Color = Gray;
	for (int i = 0; i < V[U].Neighbours.size(); ++i)
	{
		if (V[V[U].Neighbours[i]].Color == White)
			DFS_Visit(V, V[U].Neighbours[i], CompNum);
	}
	V[U].Color = Black;
	V[U].ComponentNumber = CompNum;
}

int DFS(vector<Vertex> &V)
{
	int Res = 0;
	for (int i = 0; i < V.size(); ++i)
		if (V[i].Color == White)
		{
			++Res;
			DFS_Visit(V, i, Res);
		}
	return Res;
}

int main()
{
	ifstream fin("components.in");
	ofstream fout("components.out");
	int N, M, S, E;
	fin >> N >> M;
	vector<Vertex> V(N);
	for (int i = 0; i < M; ++i)
	{
		fin >> S >> E;
		V[S - 1].Neighbours.push_back(E - 1);
		V[E - 1].Neighbours.push_back(S - 1);
	}
	fout << DFS(V) << "\n";
	for (int i = 0; i < N; ++i)
		fout << V[i].ComponentNumber << " ";
	return 0;
}