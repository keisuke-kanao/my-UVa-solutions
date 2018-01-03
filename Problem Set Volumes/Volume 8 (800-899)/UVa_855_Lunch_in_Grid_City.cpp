
/*
	UVa 855 - Lunch in Grid City

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_855_Lunch_in_Grid_City.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int nr_streets_max = 1000, nr_avenues_max = 1000, nr_friends_max = 50000;
int streets[nr_friends_max], avenues[nr_friends_max];

int main()
{
	int nr_test_cases;
	cin >> nr_test_cases;
	while (nr_test_cases--) {
		int nr_streets, nr_avenues, nr_friends;
		cin >> nr_streets >> nr_avenues >> nr_friends;
		for (int i = 0; i < nr_friends; i++)
			cin >> streets[i] >> avenues[i];
		sort(streets, streets + nr_friends);
		sort(avenues, avenues + nr_friends);
		cout << "(Street: " << streets[(nr_friends - 1) / 2] << ", Avenue: " << avenues[(nr_friends - 1) / 2] << ")\n";
	}
	return 0;
}

