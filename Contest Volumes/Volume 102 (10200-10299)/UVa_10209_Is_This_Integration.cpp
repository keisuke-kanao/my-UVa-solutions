
/*
	13.6.7 Is This Integration?
	PC/UVa IDs: 111307/10209, Popularity: A, Success rate: high Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10209_Is_This_Integration.cpp
*/

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main(int /* argc */, char** /* argv */)
{
//	const double pi = 3.14159265358979323846;
	const double pi = 2.0 * acos(0.0);
	double a;
	while(cin >> a) {
		double dotted_area = a * a * (pi / 12.0 - (2.0 - sqrt(3.0)) / 2.0);
		double rest_of_area = a * a * ((4.0 - sqrt(3.0)) / 4.0 - pi / 6.0);
		double striped_area = a * a - 4.0 * (dotted_area + rest_of_area);
		printf("%.3f %.3f %.3f\n", striped_area, dotted_area * 4.0, rest_of_area * 4.0);
	}
	return 0;
}

