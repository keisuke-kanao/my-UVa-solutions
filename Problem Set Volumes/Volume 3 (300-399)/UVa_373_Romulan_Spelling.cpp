
/*
	UVa 373 - Romulan Spelling

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_373_Romulan_Spelling.cpp
*/

/*
	'g' should be before 'p', except "epg" and "pguk"
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;

const int nr_chars_max = 70;

int main()
{
	char s[nr_chars_max + 1];
	while (gets(s)) {
		for (int i = 0, length = strlen(s); i < length; i++) {
			if (tolower(s[i]) == 'g') {
				if (i && tolower(s[i - 1]) == 'p') {
					if (i < length - 1 && tolower(s[i + 1]) == 'u' && tolower(s[i + 2]) == 'k')
						;
					else {
						int j = i;
						do {
							if (j > 1 && tolower(s[j - 2]) == 'e')
								break;
							swap(s[j - 1], s[j]);
							j--;
						}
						while (j && tolower(s[j - 1]) == 'p');
					}
				}
			}
			if (tolower(s[i]) == 'g') {
				if (i < length && tolower(s[i + 1]) == 'p') {
					if (i && tolower(s[i - 1]) == 'e')
						swap(s[i], s[i + 1]);
					else if (i < length - 2 && tolower(s[i + 2]) == 'u' && tolower(s[i + 3]) == 'k') {
						swap(s[i], s[i + 1]);
						if (i > 1 && tolower(s[i - 1]) == 'g' && tolower(s[i - 2]) == 'e')
							swap(s[i - 1], s[i]);
					}
				}
			}
		}
		puts(s);
	}
	return 0;
}

