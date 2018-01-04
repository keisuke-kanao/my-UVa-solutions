
/*
	UVa 406 - Prime Cuts

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_406_Prime_Cuts.cpp

	from ACM South Central Regionals 1996
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_SouthCen/1996/index.html)
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int primes[] = { // prime numbers that are equal to or less than 1000
	1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
	101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
	211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293,
	307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397,
	401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499,
	503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599,
	601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691,
	701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797,
	809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887,
	907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997
};

int main()
{
	int n, c;
	while (cin >> n >> c) {
		int nr = distance(primes, upper_bound(primes, primes + sizeof(primes) / sizeof(int), n));
		cout << n << ' ' << c << ':';
		int i = (nr + 1) / 2 - c, e = (nr & 1) ? i + c * 2 - 1 : i + c * 2;
		if (i >= 0 && e <= nr) {
			for ( ; i < e; i++)
				cout << ' ' << primes[i];
		}
		else {
			for (i = 0; nr; i++, nr--)
				cout << ' ' << primes[i];
		}
		cout << endl << endl;
	}
	return 0;
}

