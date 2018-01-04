
/*
	UVa 305 - Joseph

	To build using Visual Studio 2008:
		cl -EHsc -O2 -DONLINE_JUDGE UVa_305_Joseph.cpp

	Although this is similar to 151 - Power Crisis (or 440 - Eeny Meeny Moo), 
	it takes more than a few hours to calculate for k = 13.
*/

#include <iostream>
#include <cstring>
using namespace std;

#ifdef ONLINE_JUDGE
int get_random_number(int k)
{
	const int numbers[] = {0, 2, 7, 5, 30, 169, 441, 1872, 7632, 1740, 93313, 459901, 1358657, 2504881};
	return numbers[k];
}
#else
long long get_random_number(int k)
{
	const int k_max = 13;
	bool executed[k_max * 2 + 1];
	int n = k * 2;
	for (long long m = k + 1; ; m++) {
		int nr_executed = 0;
		memset(executed, 0, sizeof(executed));
		int i = 1;
		while (true) {
			long long j = m;
			while (true) {
				if (!executed[i] && !--j)
					break;
				if (++i > n)
					i = 1;
			}
#ifdef DEBUG
			cout << i << ' ';
#endif
			executed[i] = true;
			if (i > k) {
				if (++nr_executed == k) {
#ifdef DEBUG
					cout << endl;
#endif
					return m;
				}
			}
			else {
#ifdef DEBUG
				cout << endl;
#endif
				break;
			}
		}
	}
}
#endif

int main()
{
	while (true) {
		int k;
		cin >> k;
		if (!k)
			break;
		cout << get_random_number(k) << endl;
	}
	return 0;
}

