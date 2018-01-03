#include<fstream>
#include<vector>

using namespace std;

struct Vertex
{
	vector<pair<int, int>> Neighbours;
};

Vertex G[2000];
int D[2000];

void BellmannFord(int S, int N)
{
	for (int i = 0; i < N; ++i)
		D[i] = LONG_MAX / 2;
	D[S] = 0;
	bool Complete = false;
	while (!Complete)
	{
		Complete = true;
		for (int i = 0; i < N; ++i)
			for each (auto Edge in G[i].Neighbours)
				if (D[Edge.first] > D[i] + Edge.second)
				{
					D[Edge.first] = D[i] + Edge.second;
					Complete = false;
				}
	}
}

void Dijkstra(int S, int N)
{
	for (int i = 0; i < N; ++i)
		D[i] = LONG_MAX / 2;
	D[S] = 0;
	vector<bool> Used(2000);

	for (int count = 0; count < N; ++count)
	{
		int V = -1;
		for (int i = 0; i < N; ++i)
			if (!Used[i] && (V == -1 || D[i] < D[V]))
				V = i;
		if (D[V] == LONG_MAX / 2)
			break;
		Used[V] = true;
		for each (auto Edge in G[V].Neighbours)
			if (D[Edge.first] > D[V] + Edge.second)
				D[Edge.first] = D[V] + Edge.second;
	}
}

int main()
{
	ifstream fin("pathmgep.in");
	ofstream fout("pathmgep.out");
	int N, S, F;
	fin >> N >> S >> F;
	--S; --F;
	int Temp1;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
		{
			fin >> Temp1;
			if (Temp1 >= 0)
				G[i].Neighbours.push_back(make_pair(j, Temp1));
		}
	Dijkstra(S, N);
	fout << (D[F] == LONG_MAX / 2 ? -1 : D[F]);
	return 0;
}