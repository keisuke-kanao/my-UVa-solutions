
/*
	UVa 417 - Word Index

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_417_Word_Index.cpp

	from 1995 ACM East Central Regional Contest Problem F
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_EastCen/1995/index.html)
*/

#include <cstdio>
#include <cstring>
using namespace std;

bool is_valid_word(const char s[], int length)
{
	for (int i = 0; i < length - 1; i++)
		if (s[i] >= s[i + 1])
			return false;
	return true;
}

int calculate_word_index(const char s[], int length)
{
	const int word_indices[] = {0, 1, 27, 352, 2952, 17902};
		//	26 + 325 + 2600 + 14950 + 65780 = 83681

	int si = 0, wi = word_indices[length];
	char b, c = 'a';
	if (length == 5) {
		b = c;
		c++;
		for (int i = 'w' - (s[si] - 1); i <= 'w' - b; i++, c++)
			wi += (i * (i + 1) * (i + 2) * (i + 3)) / 24;
		length--;
		si++;
	}
	if (length == 4) {
		b = c;
		c++;
		for (int i = 'x' - (s[si] - 1); i <= 'x' - b; i++, c++)
			wi += (i * (i + 1) * (i + 2)) / 6;
		length--;
		si++;
	}
	if (length == 3) {
		b = c;
		c++;
		for (int i = 'y' - (s[si] - 1); i <= 'y' - b; i++, c++)
			wi += (i * (i + 1)) / 2;
		length--;
		si++;
	}
	if (length == 2) {
		b = c;
		c++;
		for (int i = 'z' - (s[si] - 1); i <= 'z' - b; i++, c++)
			wi += i;
		length--;
		si++;
	}
	wi += s[si] - c;
	return wi;
}

int main()
{
	const int nr_letters_max = 5;
	char s[nr_letters_max + 1];
	while (scanf("%s", s) != EOF) {
		int length = strlen(s);
		int wi = 0;
		if (is_valid_word(s, length))
			wi = calculate_word_index(s, length);
		printf("%d\n", wi);
	}
	return 0;
}

