
/*
	UVa 276 - Egyptian Multiplication

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_276_Egyptian_Multiplication.cpp
*/

#include <cstdio>

const int nr_chars_max = 5 * (9 + 1);

int read_egyptian_number(const char* s)
{
	static const int values[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 1000, 100, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0,
		0, 0, 10000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0
	};
	int n = 0;
	for (; *s; s++)
		n += values[*s];
	return n;
}

char* print_egyptian_number(int n, char* s)
{
	static const char* symbols = "r89n|";
	const char* ps = symbols;
	char* p = s + nr_chars_max;
	*--p = '\0';
	bool first_printed = false;
	for (int d = 10000; d; d /= 10, ps++) {
		bool printed = false;
		while (n >= d) {
			if (!printed) {
				printed = true;
				if (first_printed)
					*--p = ' ';
				else
					first_printed = true;
			}
			*--p = *ps;
			n -= d;
		}
	}
	return p;
}

int main()
{
	char s[nr_chars_max + 1], t[nr_chars_max + 1], u[nr_chars_max * 2 + 1];
	while (gets(s) && s[0]) {
		int a = read_egyptian_number(s), b = read_egyptian_number(gets(s));
		long long ia = a;
		for (int i = 1, ib = b; ib; i <<= 1, ia <<= 1, ib >>= 1) {
			char* p = print_egyptian_number(i, s);
			sprintf(u, "%-34s%s", p, print_egyptian_number(static_cast<int>(ia % 100000), t));
			if (ib & 1)
				u[s + nr_chars_max - p] = '*';
			puts(u);
		}
		printf("The solution is: %s\n", print_egyptian_number(static_cast<int>(static_cast<long long>(a) * b % 100000), s));
	}
	return 0;
}

