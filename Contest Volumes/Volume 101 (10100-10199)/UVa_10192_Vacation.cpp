
/*
	UVa 10192 - Vacation

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10192_Vacation.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_cities_max = 100;
char first_cities[nr_cities_max + 1], second_cities[nr_cities_max + 1];
int lcs_c[nr_cities_max + 1][nr_cities_max + 1];

int lcs(int first_cities_length, int second_cities_length)
{
	memset(lcs_c, 0, sizeof(lcs_c));
	for (int i = 1; i <= first_cities_length; i++)
		for (int j= 1; j <= second_cities_length; j++)
			if (first_cities[i - 1] == second_cities[j - 1])
				lcs_c[i][j] = lcs_c[i - 1][j - 1] + 1;
			else
				lcs_c[i][j] = max(lcs_c[i][j - 1], lcs_c[i - 1][j]);
	return lcs_c[first_cities_length][second_cities_length];
}

int main()
{
	for (int nr_cases = 1; ; nr_cases++) {
		gets(first_cities);
		if (first_cities[0] == '#')
			break;
		gets(second_cities);
		printf("Case #%d: you can visit at most %d cities.\n", nr_cases, lcs(strlen(first_cities), strlen(second_cities)));
	}
	return 0;
}

