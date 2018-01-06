
/*
	UVa 457 - Linear Cellular Automata

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_457_Linear_Cellular_Automata.cpp
*/

#include <iostream>
#include <cstring>
using namespace std;

const int nr_programs = 10, nr_dishes = 40, nr_days = 50;
int programs[nr_programs];
char dishes[nr_days][nr_dishes + 2];
const char symbols[] = {' ', '.', 'x', 'W'};

int main()
{
	int nr_cases;
	cin >> nr_cases;
	while (nr_cases--) {
		for (int i = 0; i < nr_programs; i++)
			cin >> programs[i];
		memset(dishes, 0, sizeof(dishes));
		dishes[0][20] = 1;
		for (int j = 1; j <= nr_dishes; j++)
			cout << symbols[dishes[0][j]];
		cout << endl;
		for (int i = 1; i < nr_days; i++) {
			for (int j = 1; j <= nr_dishes; j++) {
				dishes[i][j] = programs[dishes[i - 1][j - 1] + dishes[i - 1][j] + dishes[i - 1][j + 1]];
				cout << symbols[dishes[i][j]];
			}
			cout << endl;
		}
		if (nr_cases)
			cout << endl;
	}
	return 0;
}

