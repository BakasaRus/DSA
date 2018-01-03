#include <fstream>
#include <vector>
#include <queue>

using namespace std;

enum VColor { White, Gray, Black };

struct Vertex
{
	vector<int> Neighbours;
	VColor Color = White;
	int Distance = 0;
};

void BFS(vector<Vertex> &V, int Start)
{
	V[Start].Color = Gray;
	queue<int> Q;
	Q.push(Start);
	while (!Q.empty())
	{
		int U = Q.front();
		Q.pop();
		for (int i = 0; i < V[U].Neighbours.size(); ++i)
			if (V[V[U].Neighbours[i]].Color == White)
			{
				V[V[U].Neighbours[i]].Color = Gray;
				V[V[U].Neighbours[i]].Distance = V[U].Distance + 1;
				Q.push(V[U].Neighbours[i]);
			}
		V[U].Color = Black;
	}
}

int main()
{
	ifstream fin("pathbge1.in");
	ofstream fout("pathbge1.out");
	int N, M, S, E;
	fin >> N >> M;
	vector<Vertex> V(N);
	for (int i = 0; i < M; ++i)
	{
		fin >> S >> E;
		V[S - 1].Neighbours.push_back(E - 1);
		V[E - 1].Neighbours.push_back(S - 1);
	}
	BFS(V, 0);
	for (int i = 0; i < N; ++i)
		fout << V[i].Distance << " ";
	return 0;
}