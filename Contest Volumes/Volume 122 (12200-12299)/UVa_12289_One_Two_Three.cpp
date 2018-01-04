
/*
	UVa 12289 - One-Two-Three

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_12289_One_Two_Three.cpp
*/

#include <cstdio>
#include <cstring>

const char* ones[] = {"one", " ne", "o e", "on ", NULL};
const char* twos[] = {"two", " wo", "t o", "tw ", NULL};
const char* threes[] = {"three", " hree", "t ree", "th ee", "thr e", "thre ", NULL};

bool is_number(const char* s, int length, const char** candidates, int clength)
{
	if (length != clength)
		return false;
	for ( ; *candidates; candidates++) {
		const char *p = *candidates, *q = s;
		for ( ; *p; p++, q++)
			if (*p != ' ' && *p != *q)
				break;
		if (!*p)
			return true;
	}
	return false;
}

int main()
{
	int nw;
	scanf("%d", &nw);
	while (nw--) {
		const int nr_letters_max = 32;
		char word[nr_letters_max];
		scanf("%s", word);
		int length = strlen(word);
		int number;
		if (is_number(word, length, ones, 3))
			number = 1;
		else if (is_number(word, length, twos, 3))
			number = 2;
		else
			number = 3;
		printf("%d\n", number);
	}
	return 0;
}

