#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void QuickSearch(vector<int> &A, int l, int r, int k)
{
	int i = l, j = r, m = A[(l + r) / 2];
	while (i <= j)
	{
		while (A[i] < m) ++i;
		while (A[j] > m) --j;
		if (i <= j)
			swap(A[i++], A[j--]);
	}
	if (l < j && k <= j)
		QuickSearch(A, l, j, k);
	if (i < r && k >= i)
		QuickSearch(A, i, r, k);
}

int main()
{
	ifstream fin("kth.in");
	ofstream fout("kth.out");
	int n, k, A, B, C;
	fin >> n >> k;
	vector<int> P(n);
	fin >> A >> B >> C >> P[0] >> P[1];
	for (int i = 2; i < n; i++)
		P[i] = A * P[i - 2] + B * P[i - 1] + C;
	QuickSearch(P, 0, P.size() - 1, k - 1);
	fout << P[k - 1] << endl;
	return 0;
}