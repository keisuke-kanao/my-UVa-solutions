
/*
	UVa 1213 - Sum of Different Primes

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1213_Sum_of_Different_Primes.cpp
*/

#include <cstdio>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif

const int n_max = 1120, k_max = 14, nr_primes_max = 187;
const int primes[nr_primes_max] = {
	   2,    3,    5,    7,   11,   13,   17,   19,   23,   29,
	  31,   37,   41,   43,   47,   53,   59,   61,   67,   71,
	  73,   79,   83,   89,   97,  101,  103,  107,  109,  113,
	 127,  131,  137,  139,  149,  151,  157,  163,  167,  173,
	 179,  181,  191,  193,  197,  199,  211,  223,  227,  229,
	 233,  239,  241,  251,  257,  263,  269,  271,  277,  281,
	 283,  293,  307,  311,  313,  317,  331,  337,  347,  349,
	 353,  359,  367,  373,  379,  383,  389,  397,  401,  409,
	 419,  421,  431,  433,  439,  443,  449,  457,  461,  463,
	 467,  479,  487,  491,  499,  503,  509,  521,  523,  541,
	 547,  557,  563,  569,  571,  577,  587,  593,  599,  601,
	 607,  613,  617,  619,  631,  641,  643,  647,  653,  659,
	 661,  673,  677,  683,  691,  701,  709,  719,  727,  733,
	 739,  743,  751,  757,  761,  769,  773,  787,  797,  809,
	 811,  821,  823,  827,  829,  839,  853,  857,  859,  863,
	 877,  881,  883,  887,  907,  911,  919,  929,  937,  941,
	 947,  953,  967,  971,  977,  983,  991,  997, 1009, 1013,
	1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069,
	1087, 1091, 1093, 1097, 1103, 1109, 1117
};

int nr_ways[n_max + 1][k_max + 1][nr_primes_max];

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	for (int i = 0; i < nr_primes_max; i++)
		nr_ways[primes[i]][1][i] = 1;
	for (int k = 2; k <= k_max; k++) {
		for (int n = 1; n <= n_max; n++)
			for (int i = 0; i < nr_primes_max; i++) {
				int nr = nr_ways[n][k - 1][i];
				if (nr)
					for (int j = i + 1; j < nr_primes_max; j++)
						if (n + primes[j] <= n_max)
							nr_ways[n + primes[j]][k][j] += nr;
						else
							break;
			}
#ifdef DEBUG
		for (int n = 1; n <= n_max; n++) {
			bool printed = false;
			for (int i = 0; i < nr_primes_max; i++)
				if (nr_ways[n][k][i]) {
					printed = true;
					printf("[%d][%d][%d]:%d ", n, k, primes[i], nr_ways[n][k][i]);
				}
			if (printed)
				putchar('\n');
		}
#endif
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	while (true) {
		int n, k;
		scanf("%d %d", &n, &k);
		if (!n && !k)
			break;
		int nr = 0;
		for (int i = 0; i < nr_primes_max; i++)
			nr += nr_ways[n][k][i];
		printf("%d\n", nr);
	}
	return 0;
}

