#include <fstream>
#include <vector>

using namespace std;

struct person
{
	double p;
	int no;
};

void BubbleSort(vector<person> &a)
{
	for (int i = 0; i < a.size() - 1; i++)
		for (int j = i + 1; j < a.size(); j++)
			if (a[i].p > a[j].p) swap(a[i], a[j]);
}

int main()
{
	ifstream fin("sortland.in");
	ofstream fout("sortland.out");
	int n;
	vector<person> sl;
	fin >> n;
	sl.resize(n);
	for (int i = 0; i < n; sl[i].no = i++ + 1)
		fin >> sl[i].p;
	BubbleSort(sl);
	fout << sl[0].no << " " << sl[n / 2].no << " " << sl[n - 1].no;
	return 0;
}