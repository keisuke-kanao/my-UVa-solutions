
/*
	UVa 11038 - How Many O's

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11038_How_Many_Os.cpp

	from Waterloo ACM Programming Contest, May 27, 2006, Problem E
		(http://acm.student.cs.uwaterloo.ca/~acm00/060527/data/)
*/

#include <cstdio>
#include <cstring>

const int nr_digits_max = 10;
const int pow10s[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

char* itos(long long n, char* s, int& length)
{
	char* p = s + nr_digits_max;
	*p = '\0';
	length = 0;
	do {
		p--;
		*p = n % 10 + '0';
		n /= 10;
		length++;
	} while (n);
	return p;
}

long long stoi(const char* s, int length)
{
	long long n = 0;
	for ( ; length; length--, s++) {
		n *= 10;
		n += *s - '0';
	}
	return n;
}

long long how_many_0s(long long n)
{
	char s[nr_digits_max + 1];
	int length;
	char* p = itos(n, s, length);
	long long ctr = 1;
	for (int i = length - 1, j = 0; i; i--, j++) {
		if (p[i] != '0')
			ctr += pow10s[j] * stoi(p, i);
		else {
			ctr += pow10s[j] * (stoi(p, i) - 1) + 1;
			if (i < length - 1)
				ctr += stoi(p + i + 1, length - i - 1);
		}
	}
	return ctr;
}

int main()
{
	while (true) {
		long long m, n;
		scanf("%lld %lld", &m, &n);
		if (m < 0)
			break;
		long long ctr = how_many_0s(n);
		if (m)
			ctr -= how_many_0s(m - 1);
		printf("%lld\n", ctr);
	}
	return 0;
}

