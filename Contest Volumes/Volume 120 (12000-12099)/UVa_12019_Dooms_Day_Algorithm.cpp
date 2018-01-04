
/*
	UVa 12019 - Doom's Day Algorithm

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12019_Dooms_Day_Algorithm.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	const int days[] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
	const char* days_of_week[] = {"Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday"};

	int t;
	cin >> t;
	while (t--) {
		int m, d;
		cin >> m >> d;
		cout << days_of_week[(days[m] + d) % 7] << endl;
	}
	return 0;
}

