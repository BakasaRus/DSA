#include <fstream>
#include <vector>

using namespace std;

void BinSearch(vector<int> &a, int key, int &l, int &r)
{
	int i = 0, j = a.size();
	while (i < j)
	{
		int m = (i + j) / 2;
		if (a[m] < key)
			i = m + 1;
		else
			j = m;
	}
	// Почему i + 1: в программе нумерация с 0, а в данных с 1
	l = i + 1;
	i = 0; j = a.size();
	while (i < j)
	{
		int m = (i + j) / 2;
		if (a[m] <= key)
			i = m + 1;
		else
			j = m;
	}
	// Почему здесь просто i: при бинпоиске последнего элемента указатель
	// будет показывать элемент, СЛЕДУЮЩИЙ за нужным. i + 1 - 1 = i
	r = i;
	if (l > r)
		l = r = -1;
}

int main()
{
	ifstream fin("binsearch.in");
	ofstream fout("binsearch.out");

	int n, m;
	fin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i)
		fin >> a[i];
	fin >> m;
	for (int i = 0; i < m; ++i)
	{
		int key, l, r;
		fin >> key;
		BinSearch(a, key, l, r);
		fout << l << " " << r << endl;
	}

	return 0;
}