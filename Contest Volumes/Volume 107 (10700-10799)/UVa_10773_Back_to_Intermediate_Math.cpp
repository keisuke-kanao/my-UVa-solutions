
/*
	UVa 10773 - Back to Intermediate Math

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10773_Back_to_Intermediate_Math.cpp
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	int t;
	cin >> t;
	for (int case_nr = 1; case_nr <= t; case_nr++) {
		double d, v, u;
		cin >> d >> v >> u;
		cout << "Case " << case_nr << ": ";
		if (u == 0.0 || v == 0.0 || u <= v)
			cout << "can't determine\n";
		else {
			double fastest_time = d / u;
			double angle = asin(v / u);
			double shortest_path_time = d / (u * cos(angle));
			cout << fixed << setprecision(3) << shortest_path_time - fastest_time << endl;
		}
	}
	return 0;
}

