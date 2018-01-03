#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Person
{
	string Country, Surname;
	int Place;
};

void StableQuickSort(vector<Person> &p, int l, int r)
{
	int i = l, j = r, e = p[(l + r) / 2].Place;
	string m = p[(l + r) / 2].Country;
	while (i <= j)
	{
		while (p[i].Country < m || p[i].Country == m && p[i].Place < e) i++;
		while (p[j].Country > m || p[j].Country == m && p[j].Place > e) j--;
		if (i <= j)
			swap(p[i++], p[j--]);
	}
	if (l < j) StableQuickSort(p, l, j);
	if (i < r) StableQuickSort(p, i, r);
}

int main()
{
	ifstream fin("race.in");
	ofstream fout("race.out");
	int n;
	fin >> n;
	vector<Person> p;
	p.resize(n);
	for (int i = 0; i < n; i++)
	{
		fin >> p[i].Country >> p[i].Surname;
		p[i].Place = i + 1;
	}
	StableQuickSort(p, 0, n - 1);
	string curCountry = "";
	for (int i = 0; i < n; i++)
	{
		if (p[i].Country != curCountry)
		{
			curCountry = p[i].Country;
			fout << "=== " << curCountry << " ===" << endl;
		}
		fout << p[i].Surname << endl;
	}

	//for (int i = 0; i < n; i++)
	//	fout << p[i].Country << " " << p[i].Surname << " " << p[i].Place << endl;

	return 0;
}