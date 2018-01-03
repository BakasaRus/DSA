#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
	int K, L, R;
};

int MaxHeight(vector<Node> &Tree, int Root)
{
	if (Root == -1)
		return 0;
	else
		return max(MaxHeight(Tree, Tree[Root].L),
				   MaxHeight(Tree, Tree[Root].R)) + 1;
}

int main()
{
	ifstream fin("height.in");
	ofstream fout("height.out");

	int N;
	fin >> N;
	vector<Node> Tree(N);
	for (int i = 0; i < N; ++i)
	{
		fin >> Tree[i].K >> Tree[i].L >> Tree[i].R;
		--Tree[i].L;
		--Tree[i].R;
	}
	if (N == 0)
		fout << 0;
	else
		fout << MaxHeight(Tree, 0);

	return 0;
}