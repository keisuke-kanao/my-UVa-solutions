
/*
	UVa 11455 - Behold my quadrangle

	To build using Visual Studio 2008:
		cl -EHsc UVa_11455_Behold_my_quadrangle.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--) {
		const int nr_sides = 4;
		long long sides[nr_sides];
		cin >> sides[0] >> sides[1] >> sides[2] >> sides[3];
		sort(sides, sides + nr_sides);
		// A quadrangle has four sides that each side is shorter than half of the perimeter.
		long long perimeter = sides[0] + sides[1] + sides[2] + sides[3];
		if (sides[0] * 2 > perimeter || sides[1] * 2 > perimeter ||
			sides[2] * 2 > perimeter || sides[3] * 2 > perimeter)
			cout << "banana\n";
		else {
			if (sides[0] == sides[1]) {
				if (sides[2] == sides[3]) {
					if (sides[1] == sides[2])
						cout << "square\n";
					else
						cout << "rectangle\n";
				}
				else
					cout << "quadrangle\n";
			}
			else
				cout << "quadrangle\n";
		}
	}
	return 0;
}

