#include <fstream>

using namespace std;

int main()
{
	ifstream fin("aplusbb.in");
	ofstream fout("aplusbb.out");
	int a, b;
	fin >> a >> b;
	fout << a + b * 1ll * b;
	return 0;
}