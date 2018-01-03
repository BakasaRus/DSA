#include <fstream>
#include <vector>

using namespace std;

enum VColor { White, Gray, Black };

bool Cycles = false;
vector<int> CycleElems;

struct Vertex
{
	vector<int> Neighbours;
	VColor Color = White;
	int Parent = -1;
};

void DetectCycle(vector<Vertex> &V, int U)
{
	Cycles = true;
	int CurV = U;
	do
	{
		CycleElems.push_back(CurV);
		CurV = V[CurV].Parent;
	} while (CurV != U);
}

void DFS_Visit(vector<Vertex> &V, int U)
{
	if (Cycles) return;
	if (V[U].Color == Black) return;
	if (V[U].Color == Gray) DetectCycle(V, U);
	V[U].Color = Gray;
	for (int i = 0; i < V[U].Neighbours.size(); ++i)
	{
		V[V[U].Neighbours[i]].Parent = U;
		DFS_Visit(V, V[U].Neighbours[i]);
	}
	V[U].Color = Black;
}

void DFS(vector<Vertex> &V)
{
	for (int i = 0; i < V.size(); ++i)
		if (V[i].Color == White)
			DFS_Visit(V, i);
}

int main()
{
	ifstream fin("cycle.in");
	ofstream fout("cycle.out");
	int N, M, S, E;
	fin >> N >> M;
	vector<Vertex> V(N);
	for (int i = 0; i < M; ++i)
	{
		fin >> S >> E;
		V[S - 1].Neighbours.push_back(E - 1);
	}
	DFS(V);
	if (Cycles)
	{
		fout << "YES\n";
		for (int i = CycleElems.size() - 1; i >= 0; --i)
			fout << CycleElems[i] + 1 << " ";
	}
	else
		fout << "NO";
	return 0;
}