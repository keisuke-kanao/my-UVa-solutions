
/*
	UVa 10922 - 2 the 9s

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10922_2_the_9s.cpp
*/

#include <cstdio>
#include <cstring>

int main()
{
	while (true) {
		const int nr_digits_max = 1000;
		char number[nr_digits_max + 1];
		scanf("%s", number);
		int i, l = strlen(number);
		for (i = 0; i < l; i++)
			if (number[i] != '0')
				break;
		if (i == l)
			break;
		int s = 0, nr_degrees = 1;
		for (i = 0; i < l; i++)
			s += number[i] - '0';
		while (s > 9) {
			nr_degrees++;
			int t = 0;
			for ( ; s; s /= 10)
				t += s % 10;
			s = t;
		}
		if (s == 9)
			printf("%s is a multiple of 9 and has 9-degree %d.\n", number, nr_degrees);
		else
			printf("%s is not a multiple of 9.\n", number);
	}
	return 0;
}

