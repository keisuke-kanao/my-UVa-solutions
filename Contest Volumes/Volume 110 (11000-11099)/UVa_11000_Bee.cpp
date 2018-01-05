
/*
	UVa 11000 - Bee

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_11000_Bee.cpp
*/

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

/*
	Let M[n] be the number of male bees and F[n] be the number of female bees, then:
	M[0] = 0; F[0] = 1;
	For n >= 1,
		M[n] = M[n - 1] + F[n - 1];
		F[n] = M[n - 1] + 1;
*/

int main()
{
	vector<long long> nr_males, nr_females;
	nr_males.push_back(0);
	nr_females.push_back(1);
	while (true) {
		long long m = nr_males.back(), f = nr_females.back();
		nr_males.push_back(m + f);
		nr_females.push_back(m + 1);
#ifdef DEBUG
		cout << nr_males.back() << ' ' << nr_females.back() << endl;
#endif
		if (nr_males.back() + nr_females.back() > numeric_limits<unsigned int>::max())
			break;
	}
#ifdef DEBUG
	cout << nr_males.size() << endl;
#endif
	while (true) {
		int n;
		cin >> n;
		if (n < 0)
			break;
		cout << nr_males[n] << ' ' << nr_males[n] + nr_females[n] << endl;
	}
	return 0;
}

