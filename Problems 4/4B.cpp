#include <fstream>
#include <vector>

using namespace std;

struct Node
{
	int K, L, R;
};

void InorderTreeWalk(vector<Node> &Tree, vector<int> &Keys, int Root)
{
	if (Root != -1)
	{
		InorderTreeWalk(Tree, Keys, Tree[Root].L);
		Keys.push_back(Tree[Root].K);
		InorderTreeWalk(Tree, Keys, Tree[Root].R);
	}
}

bool isSorted(vector<int> &Keys)
{
	for (int i = 1; i < Keys.size(); ++i)
		if (Keys[i - 1] >= Keys[i])
			return false;
	return true;
}

bool isCorrect(vector<Node> &Tree, int Root)
{
	vector<int> Keys;
	InorderTreeWalk(Tree, Keys, 0);
	return isSorted(Keys);
}

int main()
{
	ifstream fin("check.in");
	ofstream fout("check.out");

	int N;
	fin >> N;
	vector<Node> Tree(N);
	for (int i = 0; i < N; ++i)
	{
		fin >> Tree[i].K >> Tree[i].L >> Tree[i].R;
		--Tree[i].L;
		--Tree[i].R;
	}

	if (N == 0 ||  isCorrect(Tree, 0))
		fout << "YES";
	else
		fout << "NO";

	return 0;
}