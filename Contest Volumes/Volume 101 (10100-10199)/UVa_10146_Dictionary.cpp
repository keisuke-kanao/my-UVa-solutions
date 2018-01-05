
/*
	UVa 10146 - Dictionary

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10146_Dictionary.cpp
*/

/*
I used a brute force approach and got AC in 0.06 sec. 
obbY, I didn't store the output and never called strlen(). 
I just compared the current word to the previous word up to the current max length of spaces while printing out spaces. 
I then printed out the current word.

a           0
 ant      1 1
  antique   2 2
 amaze      3 1
bargain     2 0
 bridge     1 1
  bride     2 2
   bribe    3 3
 born     4 1
 bucket     2 1
tart      2 0
 tan      1 1
 tram     2 1
  trolley   2 2
 t        3 1
 try      2 1
  trial     2 2
zed       3 0
double      1 0
 dorm     1 1
  do      2 2
  dormant   3 2
  donate    3 2
again     3 0
 agony      1 1
boost     2 0
 back     1 1
 born     2 1


abcde       0
 abcd     1 1
  abcd    2 2
   abc    3 3
   abc    4 3
  ab      4 2
 a        3 1

a 
 ab       1 1
  abc     2 2
  abd     3 2
  abcd    3 2

*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int nr_chars_max = 10;

const char* spaces[] = {
"", " ", "  ", "   ", "    ", "     ", "      ", "       ", "        ", "         ", "          "
};

int main()
{
	int nr_cases;
	scanf("%d", &nr_cases);
	while (getchar() != '\n')
		;
	char s[nr_chars_max + 1], t[nr_chars_max + 1];
	gets(s);
	while (nr_cases--) {
		gets(s);
		puts(s);
		char *previous = s, *current = t;
		int nr_spaces = 1;
		while (gets(current) && current[0]) {
			int i;
			for (i = 0; i < nr_spaces; i++)
				if (!previous[i] || !current[i] || previous[i] != current[i])
					break;
			printf("%s%s\n", spaces[i], current);
			nr_spaces = i + 1;
			swap(previous, current);
		}
		if (nr_cases)
			putchar('\n');
	}
	return 0;
}

