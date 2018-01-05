
/*
	UVa 10203 - Snow Clearing

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10203_Snow_Clearing.cpp

	from Waterloo Programming Contest, September 29, 2001, Problem C
*/

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

/*
	Since the streets form Eulerian cycle, they can be traversed by passing each streat only once from the hanger.
*/

int main()
{
	string line;
	getline(cin, line);
	istringstream iss(line);
	int nr_cases;
	iss >> nr_cases;
	iss.clear();
	getline(cin, line);
	while (nr_cases--) {
		getline(cin, line);
/*
		iss.str(line);
		int x, y;
		iss >> x >> y;
		iss.clear();
*/
		double d = 0.0;
		while (getline(cin, line) && line.length()) {
			iss.str(line);
			int xs, ys, xe, ye;
			iss >> xs >> ys >> xe >> ye;
			iss.clear();
			d += hypot(static_cast<double>(xe - xs), static_cast<double>(ye - ys));
		}
		double m = d * 60 / 10000.0 /* d * 2 * 60 / 20000.0 */;
		int minutes = static_cast<int>(m + 0.5);
		printf("%d:%02d\n", minutes / 60, minutes % 60);
		if (nr_cases)
			putchar('\n');
	}
}

/*
Sample Input

1

0 0
0 0 10000 10000
5000 -10000 5000 10000
5000 10000 10000 10000

Sample Output

3:55

*/

