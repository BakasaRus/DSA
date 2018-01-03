#include <fstream>
#include <vector>

using namespace std;

long long result = 0;

void merge(vector<int> &a, int l, int m, int r)
{
	vector<int> res;
	res.resize(r - l);
	int i = 0, j = 0;
	while (l + i < m && m + j < r)
		if (a[l + i] <= a[m + j])
		{
			res[i + j] = a[l + i];
			i++;
		}
		else
		{
			res[i + j] = a[m + j];
			j++;
			result += m - (l + i);
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
	ifstream fin("inversions.in");
	ofstream fout("inversions.out");
	int n;
	fin >> n;
	vector<int> a;
	a.resize(n);
	for (int i = 0; i < n; i++)
		fin >> a[i];
	mergeSort(a, 0, n);
	//for (int i = 0; i < n - 1; i++)
	//	for (int j = i + 1; j < n; j++)
	//		if (i < j && a[i] > a[j])
	//			result++;
	fout << result;
	return 0;
}