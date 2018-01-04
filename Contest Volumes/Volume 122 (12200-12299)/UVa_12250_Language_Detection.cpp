
/*
	UVa 12250 - Language Detection

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_12250_Language_Detection.cpp
*/

#include <cstdio>
#include <cstring>

int main()
{
	const char* hellos[] = {"HELLO", "HOLA", "HALLO", "BONJOUR", "CIAO", "ZDRAVSTVUJTE"};
	const char* languages[] = {"ENGLISH", "SPANISH", "GERMAN", "FRENCH", "ITALIAN", "RUSSIAN", "UNKNOWN"};
	for (int case_nr = 1; ; case_nr++) {
		const int nr_chars_max = 14;
		char s[nr_chars_max + 1];
		scanf("%s", s);
		if (!strcmp(s, "#"))
			break;
		size_t i;
		for (i = 0; i < sizeof(hellos) / sizeof(const char*); i++)
			if (!strcmp(s, hellos[i]))
				break;
		printf("Case %d: %s\n", case_nr, languages[i]);
	}
	return 0;
}

