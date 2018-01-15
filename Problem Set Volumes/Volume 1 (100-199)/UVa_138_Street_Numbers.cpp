
/*
	UVa 138 - Street Numbers

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_138_Street_Numbers.cpp
*/

#include <cstdio>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <iostream>
#include <ctime>
using namespace std;
#endif

/*
	Let m be the house number and n be the last number.
	Consider the sum from 1 to n.
		1 + 2 + ... + (m - 1) + m + (m + 1) + ... + n.
	For this problem, 
		1 + 2 + ... + (m - 2) + (m - 1) = (m + 1) + ... + (n - 1) + n.
	Or,
		1 + 2 + ... + {m - 1 - (n - m)} = {(m + 1) - {(m - 2 - (n - m)}} + ... + {n - (m - 1)}
		1 + 2 + ... + {2 * m - (n + 1)} = {n - (m - 1)} + ... + {n - (m - 1)}
	The left hand side is the sum from 1 to {2 * m - (n + 1)} and 
	there are (n - m) items on the right hand side, then:
		(1 / 2) * {2 * m - (n + 1)} * (2 * m - n) = {n - (m - 1)} * (n - m)
	Arranging the equation results in:
		m^2 = (1 / 2) * n * (n + 1).

         6         8
        35        49
       204       288
      1189      1681
      6930      9800
     40391     57121
    235416    332928
   1372105   1940449
   7997214  11309768
  46611179  65918161
*/

int calculate_house_number(int last_number)
{
	double sl = static_cast<double>(last_number) * (static_cast<double>(last_number) + 1.0) / 2.0;
	int house_number = static_cast<int>(sqrt(sl));
	return (static_cast<double>(house_number) * static_cast<double>(house_number) == sl) ? house_number : -1;
}

int main()
{
	const int nr_printed_max = 10;
	int nr_printed = 0;
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	for (int last_number = 3; ; last_number++) {
		int house_number = calculate_house_number(last_number);
		if (house_number != -1) {
			printf("%10d%10d\n", house_number, last_number);
			if (++nr_printed == nr_printed_max)
				break;
		}
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

