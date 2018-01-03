
/*
	UVa 641 - Do the Untwist

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_641_Do_the_Untwist.cpp
*/

#include <cstdio>
#include <cstring>

int main()
{
	const int nr_letters = 28, nr_chars_max = 70;
	char ct[nr_chars_max + 1] /* cipher text */, pt[nr_chars_max + 1] /* plain text */;
	int cc[nr_chars_max] /* cipher code */, pc[nr_chars_max] /* plain code */;
	while (true) {
		int k;
		scanf("%d", &k);
		if (!k)
			break;
		scanf("%s", ct);
		int n = strlen(ct);
		for (int i = 0; i < n; i++) { // convert the cipher text to cipher code
			if (ct[i] == '_')
				cc[i] = 0;
			else if (ct[i] == '.')
				cc[i] = nr_letters - 1;
			else
				cc[i] = ct[i] - 'a' + 1;
		}
		for (int i = 0; i < n; i++) { // convert the cipher code to plain code
			int j = k * i % n;
			pc[j] = (cc[i] + i) % nr_letters;
		}
		for (int i = 0; i < n; i++) { // convert the plain code to plain text
			if (!pc[i])
				pt[i] = '_';
			else if (pc[i] == nr_letters - 1)
				pt[i] = '.';
			else
				pt[i] = pc[i] + 'a' - 1;
		}
		pt[n] = '\0';
		printf("%s\n", pt);
	}
	return 0;
}

