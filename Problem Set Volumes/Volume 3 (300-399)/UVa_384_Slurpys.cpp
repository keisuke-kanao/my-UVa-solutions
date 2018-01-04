
/*
	UVa 384 - Slurpys

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_384_Slurpys.cpp

	from ACM Mid-Atlantic Regionals 1996
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_MidAtl/1996/index.html)
*/

#include <cstdio>
#include <cstring>

int is_slump(const char* s, int i, int length)
{
	int si = i;
	if (i >= length || s[i] != 'D' && s[i] != 'E')
		return -1;
	if (++i == length || s[i] != 'F')
		return -1;
	for (i++; i < length; i++)
		if (s[i] != 'F')
			break;
	if (i == length)
		return -1;
	else if (s[i] == 'G')
		return i - si + 1;
	else {
		int slump_length = is_slump(s, i, length);
		return (slump_length > 0) ? i + slump_length - si : -1;
	}
}

int is_slimp(const char* s, int i, int length)
{
	int si = i;
	if (i >= length || s[i] != 'A')
		return -1;
	if (++i == length)
		return -1;
	else if (s[i] == 'H')
		return 2;
	else if (s[i] == 'B') {
		int slimp_length = is_slimp(s, ++i, length);
		return (slimp_length > 0 && i + slimp_length < length && s[i + slimp_length] == 'C') ? i + slimp_length - si + 1 : -1;
	}
	else {
		int slump_length = is_slump(s, i, length);
		return (slump_length > 0 && i + slump_length < length && s[i + slump_length] == 'C') ? i + slump_length - si + 1 : -1;
	}
}

bool is_slurpys(const char* s)
{
	int length = strlen(s);
	int slimp_length = is_slimp(s, 0, length);
	if (slimp_length > 0) {
		int slump_length = is_slump(s, slimp_length, length);
		return (slimp_length + slump_length == length) ? true : false;
	}
	else
		return false;
}

int main()
{
	int n;
	scanf("%d", &n);
	printf("SLURPYS OUTPUT\n");
	while (n--) {
		const int nr_chars_max = 60;
		char s[nr_chars_max + 1];
		scanf("%s", s);
		printf("%s\n", ((is_slurpys(s)) ? "YES" : "NO"));
	}
	printf("END OF OUTPUT\n");
	return 0;
}

