
/*
	UVa 739 - Soundex Indexing

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_739_Soundex_Indexing.cpp
*/

#include <cstdio>

char soundex_code(char c)
{
	char cc = 0;
	switch (c) {
	case 'B': case 'P': case 'F': case 'V':
		cc = '1'; break;
	case 'C': case 'S': case 'K': case'G': case 'J': case 'Q': case 'X': case 'Z':
		cc = '2'; break;
	case 'D': case 'T':
		cc = '3'; break;
	case 'L':
		cc = '4'; break;
	case 'M': case 'N':
		cc = '5'; break;
	case 'R':
		cc = '6'; break;
	default:
		break;
	}
	return cc;
}

int main()
{
	printf("         NAME                     SOUNDEX CODE\n");
	const int nr_chars_max = 20, nr_coded_length = 4;
	char name[nr_chars_max + 1], code[nr_chars_max + 1];
	while (scanf("%s", name) != EOF) {
		const char* p = name;
		char pcc = soundex_code(*p);
		int coded_length = 0;
		code[coded_length++] = *p++;
		for ( ; *p; *p++) {
			char cc = soundex_code(*p);
			if (cc && cc != pcc)
				code[coded_length++] = cc;
			pcc = cc;
		}
		while (coded_length < nr_coded_length)
			code[coded_length++] = '0';
		code[nr_coded_length] = '\0';
		printf("         %-25s%s\n", name, code);
	}
	printf("                   END OF OUTPUT\n");
	return 0;
}

