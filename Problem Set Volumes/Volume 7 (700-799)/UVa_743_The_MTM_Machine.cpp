
/*
	UVa 743 - The MTM Machine

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_743_The_MTM_Machine.cpp
*/

#include <cstdio>
#include <cstring>

const int nr_digits_max = 1000;
char s[nr_digits_max + 1], t[nr_digits_max + 1];

void associate(int si, int length, char* s, char* t)
{
	if (--si >= 0 && s[si] == '3') {
		memcpy(t, s, si);
		memcpy(t + si, s + si + 1, length - si - 1);
		t[length - 1] = '2';
		memcpy(t + length, s + si + 1, length - si); // including '\0'
		associate(si, length * 2 - si - 1, t, s);
	}
	else
		puts(s);
}

bool MTM()
{
	if (strchr(s, '0'))
		return false;
	else {
		int length = strlen(s);
		for (int i = 0; i < length; i++) {
			if (s[i] == '2') {
				if (i < length - 1) {
					// remove '2'
					memcpy(t, s, i);
					memcpy(t + i, s + i + 1, length - i + 1); // including '\0'
					associate(i, length - 1, t, s); 
					return true;
				}
				else
					break;
			}
			else if (s[i] != '3')
				break;
		}
		return false;
	}
}

int main()
{
	while (true) {
		scanf("%s", s);
		if (!strcmp(s, "0"))
			break;
		if (!MTM())
			puts("NOT ACCEPTABLE");
	}
	return 0;
}

