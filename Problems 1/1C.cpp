#include <fstream>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 1002;
int field[MAX_SIZE][MAX_SIZE], sum[MAX_SIZE][MAX_SIZE];

int main()
{
	ifstream fin("turtle.in");
	ofstream fout("turtle.out");
	int h, w;
	fin >> h >> w;
	for (int i = 1; i <= h; i++)
		for (int j = 1; j <= w; j++)
			fin >> field[i][j];
	for (int i = h; i >= 1; i--)
		for (int j = 1; j <= w; j++)
			sum[i][j] = max(sum[i + 1][j], sum[i][j - 1]) + field[i][j];
	fout << sum[1][w];
	return 0;
}