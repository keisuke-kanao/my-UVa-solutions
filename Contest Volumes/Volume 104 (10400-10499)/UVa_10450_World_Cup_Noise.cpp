
/*
	UVa 10450 - World Cup Noise

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10450_World_Cup_Noise.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	const int n_max = 51;
	long long answers[n_max + 1];
	answers[0] = 0;
	answers[1] = 2; answers[2] = 3;
	for (int i = 3; i <= n_max; i++)
		answers[i] = answers[i - 1] + answers[i - 2];
	int nr_scenarios;
	cin >> nr_scenarios;
	for (int sc = 1; sc <= nr_scenarios; sc++) {
		int n;
		cin >> n;
		cout << "Scenario #" << sc << ":\n" << answers[n] << endl << endl;
	}
	return 0;
}

