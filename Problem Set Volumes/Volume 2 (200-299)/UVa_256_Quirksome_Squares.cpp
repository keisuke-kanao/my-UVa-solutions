
/*
	UVa 256 - Quirksome Squares

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_256_Quirksome_Squares.cpp
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

#ifdef ONLINE_JUDGE

const int quirksome_numbers_2[] = {0, 1, 81, -1},
	quirksome_numbers_4[] = {0, 1, 2025, 3025, 9801, -1},
	quirksome_numbers_6[] = {0, 1, 88209, 494209, 998001, -1},
	quirksome_numbers_8[] = {0, 1, 4941729, 7441984, 24502500, 25502500, 52881984, 60481729, 99980001, -1};

const int* quirksome_numbers[] = {
	quirksome_numbers_2, quirksome_numbers_4, quirksome_numbers_6, quirksome_numbers_8
};

int main() {
	int n;
	while (cin >> n) {
		const int* qn = quirksome_numbers[n / 2 - 1];
		for ( ; *qn != -1; qn++)
			cout << setfill('0') << setw(n) << *qn << endl;
	}
	return 0;
}

#else // !ONLINE_JUDGE

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	const int max_numbers[] = {0, 99, 9999, 999999, 99999999};
	const int divisors[] = {0, 10, 100, 1000, 10000};
	int n;
	while (cin >> n) {
		int max_n = max_numbers[n / 2], d = divisors[n / 2];
		for (int i = 0; i <= max_n; i++)
			if (i / d + i % d == sqrt(static_cast<double>(i)))
				cout << setfill('0') << setw(n) << i << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

#endif // ONLINE_JUDGE

