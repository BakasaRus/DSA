#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

bool isAbove(vector<double> &h)
{
	for (int i = 2; i < h.size(); ++i)
	{
		h[i] = (h[i - 1] + 1) * 2 - h[i - 2];
		if (h[i] <= 0)
			return false;
	}
	return true;
}

int main()
{
	ifstream fin("garland.in");
	ofstream fout("garland.out");
	int n;
	fin >> n;
	vector<double> h(n);
	fin >> h[0];

	double min = 0, max = h[0];
	while (true)
	{
		h[1] = (min + max) / 2;
		if (h[1] == min || h[1] == max)
			break;
		if (isAbove(h))
			max = h[1];
		else
			min = h[1];
	}
	// Когда у тебя на тесте "4 1000" выдавало -0.00
	fout << fixed << setprecision(2) << abs(h[n - 1]);
	return 0;
}