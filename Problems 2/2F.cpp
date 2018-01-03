#include <fstream>
#include <vector>
#include <string>

using namespace std;

void CountingSort(vector<string> &s, int phase)
{
	const int range = 'z' - 'A' + 1;
	vector<int> c(range);
	vector<string> b(s.size());
	for (int i = 0; i < range; i++)
		c[i] = 0;
	for (int i = 0; i < s.size(); i++)
		c[s[i][phase] - 'A']++;
	for (int i = 1; i < range; i++)
		c[i] = c[i] + c[i - 1];
	for (int i = s.size() - 1; i >= 0; i--)
		b[--c[s[i][phase] - 'A']] = s[i];
	s = b;
}

void RadixSort(vector<string> &s, int m, int k)
{
	for (int i = m - 1; i >= m - k; i--)
		CountingSort(s, i);
}

int main()
{
	ifstream fin("radixsort.in");
	ofstream fout("radixsort.out");
	int n, m, k;
	fin >> n >> m >> k;
	vector<string> s(n);
	for (int i = 0; i < n; i++)
		fin >> s[i];
	RadixSort(s, m, k);
	for (int i = 0; i < n; i++)
		fout << s[i] << endl;
	return 0;
}