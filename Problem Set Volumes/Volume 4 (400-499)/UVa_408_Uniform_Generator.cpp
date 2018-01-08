
/*
	UVa 408 - Uniform Generator

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_408_Uniform_Generator.cpp

	from ACM South Central Regional Programming Contest 1996 Problem #3
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_SouthCen/1996/index.html)

	The ACM ICPC Problem Set Archive
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive.html)
*/

/*
	This problem can be solved mathematically. 
	The solution is "Good Choice" if and only if GCD(STEP, MOD) = 1, "Bad Choice" otherwise.
*/

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

bool is_good_choice(int step, int mod)
{
	int s = 0, nr_generated = 1;
	vector<bool> seeds(mod, false);
	seeds[s] = true;
	while (true) {
		s = (s + step) % mod;
		if (seeds[s])
			break;
		seeds[s] = true;
		if (++nr_generated == mod)
			break;
	}
	return (nr_generated == mod) ? true : false;
}

int main()
{
	int step, mod;
	while (cin >> step >> mod) {
		cout << setfill(' ') << setw(10) << step << setw(10) << mod <<
			((is_good_choice(step, mod)) ? "    Good Choice\n\n" : "    Bad Choice\n\n");
	}
	return 0;
}

