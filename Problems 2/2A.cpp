#include <fstream>
#include <vector>

using namespace std;

void qSort(vector<int> &a, int l, int r)
{
	int i = l, j = r, e = a[(l + r) / 2], t;
	while (i <= j)
	{
		while (a[i] < e) i++;
		while (a[j] > e) j--;
		if (i <= j)
		{
			t = a[i];
			a[i] = a[j];
			a[j] = t;
			i++; j--;
		}
	}
	if (l < j) qSort(a, l, j);
	if (i < r) qSort(a, i, r);
}

void merge(vector<int> &a, int l, int m, int r)
{
	vector<int> res;
	res.resize(r - l);
	int i = 0, j = 0;
	while (l + i < m && m + j < r)
		if (a[l + i] < a[m + j])
		{
			res[i + j] = a[l + i];
			i++;
		}
		else
		{
			res[i + j] = a[m + j];
			j++;
		}
	while (l + i < m)
	{
		res[i + j] = a[l + i];
		i++;
	}
	while (m + j < r)
	{
		res[i + j] = a[m + j];
		j++;
	}
	for (int it = 0; it < i + j; it++)
	{
		a[l + it] = res[it];
	}
}

void mergeSort(vector<int> &a, int l, int r)
{
	if (l + 1 >= r)
		return;
	int m = (l + r) / 2;
	mergeSort(a, l, m);
	mergeSort(a, m, r);
	merge(a, l, m, r);
}

int main()
{
	ifstream fin("sort.in");
	ofstream fout("sort.out");
	int n;
	fin >> n;
	vector<int> a;
	a.resize(n);
	for (int i = 0; i < n; i++)
		fin >> a[i];
	//qSort(a, 0, n - 1);
	mergeSort(a, 0, n);
	for (int i = 0; i < n; i++)
		fout << a[i] << " ";
	return 0;
}