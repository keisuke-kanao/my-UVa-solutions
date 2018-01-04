
/*
	UVa 11479 - Is this the easiest problem?

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11479_Is_this_the_easiest_problem.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	for (int case_nr = 1; case_nr <= t; case_nr++) {
		long long a, b, c;
		cin >> a >> b >> c;
		cout << "Case " << case_nr << ": ";
		if (a <= 0 || b <= 0 || c <= 0 || a + b <= c || b + c <= a || c + a <= b)
			cout << "Invalid\n";
		else if (a == b && b == c)
			cout << "Equilateral\n";
		else if (a == b || b == c || c == a)
			cout << "Isosceles\n";
		else
			cout << "Scalene\n";
	}
	return 0;
}

