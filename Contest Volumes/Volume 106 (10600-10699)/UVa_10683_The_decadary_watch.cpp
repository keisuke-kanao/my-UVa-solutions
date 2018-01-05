
/*
	UVa 10683 - The decadary watch

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10683_The_decadary_watch.cpp
*/

#include <cstdio>

int main()
{
	const int nr_time_units = 4;
	const int t_time_units[nr_time_units] = {24, 60, 60, 100};
	const int t_time_chars = 8;
	char t_time[t_time_chars + 1];
	while (scanf("%s", t_time) != EOF) {
		long long t = 0;
		for (int i = 0; i < nr_time_units; i++) {
			t *= t_time_units[i];
			t += (t_time[i * 2] - '0') * 10 + (t_time[i * 2 + 1] - '0');
		}
		long long t_time_divisor = 8640000, d_time_divisor = 10000000;
		printf("%07lld\n", (t * d_time_divisor) / t_time_divisor);
	}
	return 0;
}

