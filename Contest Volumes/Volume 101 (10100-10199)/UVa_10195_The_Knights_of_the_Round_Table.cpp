
/*
	13.6.3 The Knights of the Round Table
	PC/UVa IDs: 111303/10195, Popularity: A, Success rate: average Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10195_The_Knights_of_the_Round_Table.cpp
*/

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

/*
	Let r be the The radius of the incircle (also known as the inradius) of a triangle.
	r = sqrt((s - a) * (s - b) * (s - c) / s), where s = (a + b + c) / 2.
*/

double inradius_of_triangle(double a, double b, double c)
{
	if (a == 0.0 || b == 0.0 || c == 0.0)
		return 0.0;
	double s = (a + b + c) / 2.0;
	return sqrt((s - a) * (s - b) * (s - c) / s);
}

int main(int /* argc */, char** /* argv */)
{
	double a, b, c;
	while (cin >> a >> b >> c)
		printf("The radius of the round table is: %.03f\n", inradius_of_triangle(a, b, c));
	return 0;
}

