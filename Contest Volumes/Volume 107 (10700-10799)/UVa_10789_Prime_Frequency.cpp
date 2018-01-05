
/*
	UVa 10789 - Prime Frequency

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10789_Prime_Frequency.cpp
*/

#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
using namespace std;

bool is_prime(int n)
{
	if (n == 1)
		return false;
	else if (n == 2)
		return true;
	else if (!(n % 2))
		return false;
	else {
		for (int i = 3; i <= static_cast<int>(sqrt(static_cast<double>(n))) + 1; i += 2)
			if (!(n % i))
				return false;
	}
	return true;
}

int main()
{
	const int nr_numbers = 10, nr_letters = 26;
	int numbers[nr_numbers], uppercase_letters[nr_letters], lowercase_letters[nr_letters];
	int t;
	scanf("%d", &t);
	for (int c = 1; c <= t; c++) {
		memset(numbers, 0, sizeof(numbers));
		memset(uppercase_letters, 0, sizeof(uppercase_letters));
		memset(lowercase_letters, 0, sizeof(lowercase_letters));
		const int nr_chars_max = 2001;
		char s[nr_chars_max];
		scanf("%s", s);
		for (const char* p = s; *p; p++) {
			char d = *p;
			if (isdigit(d))
				numbers[d - '0']++;
			else if (isupper(d))
				uppercase_letters[d - 'A']++;
			else
				lowercase_letters[d - 'a']++;
		}
		printf("Case %d: ", c);
		bool found_primes = false;
		for (int i = 0; i < nr_numbers; i++)
			if (is_prime(numbers[i])) {
				found_primes = true;
				putchar(i + '0');
			}
		for (int i = 0; i < nr_letters; i++)
			if (is_prime(uppercase_letters[i])) {
				found_primes = true;
				putchar(i + 'A');
			}
		for (int i = 0; i < nr_letters; i++)
			if (is_prime(lowercase_letters[i])) {
				found_primes = true;
				putchar(i + 'a');
			}
		if (found_primes)
			putchar('\n');
		else
			printf("empty\n");
	}
	return 0;
}

