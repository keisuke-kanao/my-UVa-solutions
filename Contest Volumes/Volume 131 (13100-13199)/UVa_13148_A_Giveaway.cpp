
/*
	UVa 13148 - A Giveaway

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_13148_A_Giveaway.cpp
*/

#include <cstdio>
#include <cstdlib>

const int specials[] = {
	1, 64, 729, 4096, 15625, 46656, 117649, 262144, 531441, 1000000, 
	1771561, 2985984, 4826809, 7529536, 11390625, 16777216, 24137569, 34012224, 47045881, 64000000,
	85766121
};

int compare_int(const void* a, const void* b)
{
	return *reinterpret_cast<const int*>(a) - *reinterpret_cast<const int*>(b);
}

int main()
{
	while (true) {
		int i;
		scanf("%d", &i);
		if (!i)
			break;
		puts((bsearch(&i, specials, sizeof(specials) / sizeof(int), sizeof(int), compare_int)) ?
			"Special" : "Ordinary");
	}
	return 0;
}

