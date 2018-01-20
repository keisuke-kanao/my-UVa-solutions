
/*
	12.6.6 (2/3/4)-D Sqr/Rects/Cubes/Boxes?
	PC/UVa IDs: 111206/10177, Popularity: B, Success rate: high Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10177_Sqr_Rects_Cubes_Boxes.cpp
*/

/*
	For the length of one side of grid n and dimention d, 
	Let S(n, d) be the number of squares/cubes , R(n, d) be the number of rectangles/boxes, then:
		S(n, d) = Σpow(i, d) (i = 1 to n)
		R(n, d) = pow(Σi, d) - S(n, d)

	Σi = (1 / 2) * n * (n + 1)
	Σpow(i, 2) = (1 / 6) * n * (n + 1) * (2 * n + 1)
	Σpow(i, 3) = (1 / 4) * n * n * (n + 1) * (n + 1)
	Σpow(i, 4) = (1 / 30) * n * (n + 1) * (2 * n + 1) * (3 * n * n + 3 * n - 1)
*/

#include <iostream>
using namespace std;

long long power_of_sum(long long n, int d)
{
	long long s = n * (n + 1) / 2;
	long long ps = s;
	while (--d)
		ps *= s;
	return ps;
}

long long s(long long n, int d)
{
	if (d == 2)
		return n * (n + 1) * (2 * n + 1) / 6;
	else if (d == 3)
		return n * n * (n + 1) * (n + 1) / 4;
	else
		return n * (n + 1) * (2 * n + 1) * (3 * n * n + 3 * n - 1) / 30;
}

long long r(int n, int d)
{
	return power_of_sum(n, d) - s(n, d);
}

int main(int /* argc */, char ** /* argv */)
{
	int n;
	while (cin >> n) {
		cout << s(n, 2) << ' ' << r(n, 2) << ' ' << s(n, 3) << ' ' << r(n, 3) << ' ' <<
			s(n, 4) << ' ' << r(n, 4) << endl;
	}
}

