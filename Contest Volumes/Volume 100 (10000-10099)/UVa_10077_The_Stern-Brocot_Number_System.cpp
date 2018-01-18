
/*
	5.9.7 The Stern-Brocot Number System
	PC/UVa IDs: 110507/10077, Popularity: C, Success rate: high Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10077_The_Stern-Brocot_Number_System.cpp
*/

#include <iostream>
#include <string>
#include <utility>
using namespace std;

typedef pair<int, int> fraction; // first field is numerator, second field is denominator

string stern_brocot_number(fraction f, fraction left, fraction right)
{
#ifdef DEBUG
cout << left.first << ',' << left.second << ' ' << right.first << ',' << right.second;
#endif
	fraction middle(left.first + right.first, left.second + right.second);
	if (middle == f) {
#ifdef DEBUG
		cout << endl;
#endif
		return string();
	}
	int m = f.first * middle.second - f.second * middle.first;
	if (m < 0) {
#ifdef DEBUG
		cout << " L\n";
#endif
		return 'L' + stern_brocot_number(f, left, middle);
	}
	else {
#ifdef DEBUG
		cout << " R\n";
#endif
		return 'R' + stern_brocot_number(f, middle, right);
	}
}

int main(int /* argc */, char** /* argv */)
{
	int m, n;
	while (cin >> m >> n) {
		if (m == 1 && n == 1)
			break;
		fraction f(m, n), left(0, 1), right(1, 0);
		cout << stern_brocot_number(f, left, right) << endl;
	}
	return 0;
}

