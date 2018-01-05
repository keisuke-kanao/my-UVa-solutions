
/*
	UVa 10554 - Calories from Fat

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10554_Calories_from_Fat.cpp

	from Waterloo local contest, 27 September, 2003, Problem A
		(http://acm.student.cs.uwaterloo.ca/~acm00/030927/data/)
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	const int nr_nutritions = 5;
	const int calories_per_g[nr_nutritions] = {9, 4, 4, 4, 7};

	while (true) {
		string s;
		getline(cin, s);
		if (s[0] == '-')
			break;
		double fat = 0.0, total = 0.0, calories[nr_nutritions];
		while (true) {
			istringstream iss(s);
			double p = 100.0, c = 0.0;
			for (int i = 0; i < nr_nutritions; i++) {
				int q;
				char u;
				iss >> q >> u;
				switch (u) {
				case 'g':
					calories[i] = q * calories_per_g[i];
					c += calories[i];
					break;
				case 'C':
					calories[i] = q;
					c += q;
					break;
				case '%':
					calories[i] = -q;
					p -= q;
					break;
				}
			}
			double t = 0.0;
			if (p < 100.0) { // some are represented by %
				t = 100.0 * c / p; // total calories
				for (int i = 0; i < nr_nutritions; i++) {
					if (calories[i] < 0.0)
						calories[i] = t * (-calories[i]) /100.0;
#ifdef DEBUG
					cout << calories[i] << ' ';
#endif
				}
#ifdef DEBUG
				cout << t << endl;
#endif
			}
			else {
				for (int i = 0; i < nr_nutritions; i++) {
#ifdef DEBUG
					cout << calories[i] << ' ';
#endif
					t += calories[i];
				}
#ifdef DEBUG
				cout << t << endl;
#endif
			}
			fat += calories[0];
			total += t;
			getline(cin, s);
			if (s[0] == '-')
				break;
		}
		cout << fixed << setprecision(0) << fat * 100.0 / total << "%\n";
	}
	return 0;
}

