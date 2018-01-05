
/*
	UVa 11203 - Can you decide it for ME?

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11203_Can_you_decide_it_for_ME.cpp
*/

#include <cstdio>

bool theorem(const char* s)
{
	int i = 0, nrs[3];
		// nrs[0] is the number of '?' before 'M', nrs[1] is the number of '?' between 'M' and 'E',
		// nrs[2] is the number of '?' after 'E'
	const char* q;
	for (q = s; *s; s++) {
		if (*s == 'M') {
			if (i != 0)
				return false;
			if ((nrs[i++] = s - q) <= 0)
				return false;
			q = s + 1;
		}
		else if (*s == 'E') {
			if (i != 1)
				return false;
			if ((nrs[i++] = s - q) <= 0)
				return false;
			q = s + 1;
		}
		else if (*s != '?')
			return false;
	}
	if (i != 2)
		return false;
	if ((nrs[2] = s - q) <= 0)
		return false;
	while (nrs[1] > 1) {
		if (nrs[2] < 2)
			return false;
		nrs[1]--; nrs[2]--;
	}
	return nrs[0] == nrs[2] - 1;
}

int main()
{
	int N;
	scanf("%d", &N);
	while (N--) {
		const int nr_chars_max = 50;
		char s[nr_chars_max + 1];
		scanf("%s", s);
		puts((theorem(s)) ? "theorem" : "no-theorem");
	}
	return 0;
}

