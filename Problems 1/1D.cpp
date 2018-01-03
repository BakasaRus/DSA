#include <fstream>
#include <vector>

using namespace std;

void BubbleSort(vector<int> &a)
{
	for (int i = 0; i < a.size() - 1; i++)
		for (int j = i + 1; j < a.size(); j++)
			if (a[i] > a[j]) swap(a[i], a[j]);
}

int main()
{
	ifstream fin("smallsort.in");
	ofstream fout("smallsort.out");
	int n, t;
	vector<int> a;
	fin >> n;
	a.resize(n);
	for (int i = 0; i < n; i++)
		fin >> a[i];
	BubbleSort(a);
	for (int i = 0; i < a.size(); i++)
		fout << a[i] << " ";
	return 0;
}