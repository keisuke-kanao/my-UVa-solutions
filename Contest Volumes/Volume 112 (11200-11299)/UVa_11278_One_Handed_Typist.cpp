
/*
	UVa 11278 - One-Handed Typist

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11278_One_Handed_Typist.cpp
*/

#include <cstdio>

int main()
{
	const char qwerty_2_dvorak[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		' ', '!', '_', '#', 'Q', 'J', 'M', '-', 'P', '?', 'F', '}', 'v', '[', 'g', '\'',
		'/', '1', '2', '3', 'q', 'j', 'l', 'm', 'f', 'p', 'K', 'k', 'V', ']', 'G', '"',
		'@', '&', 'I', 'X', '(', '^', 'A', 'E', 'H', 'U', 'T', 'D', 'C', 'W', 'N', 'Y',
		'B', '$', '>', '*', 'O', 'S', '<', '%', 'Z', 'R', ')', ';', '\\', '=', 'L', '{',
		'`', '7', 'i', 'x', '9', '6', 'a', 'e', 'h', 'u', 't', 'd', 'c', 'w', 'n', 'y',
		'b', '4', '.', '8', 'o', 's', ',', '5', 'z', 'r', '0', ':', '|', '+', '~', 0
	};
	const int nr_chars_max = 1000;
	char s[nr_chars_max + 1];
	while (gets(s)) {
		for (char* p = s; *p; p++)
			*p = qwerty_2_dvorak[*p];
		puts(s);
	}
	return 0;
}

