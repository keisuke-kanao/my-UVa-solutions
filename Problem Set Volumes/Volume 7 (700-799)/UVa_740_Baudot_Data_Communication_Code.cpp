
/*
	UVa 740 - Baudot Data Communication Code

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_740_Baudot_Data_Communication_Code.cpp

	from 1988 ACM East Central Regional Programming Contest Problem #1
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_EastCen/1988/index.html)
*/

#include <cstdio>

int main()
{
	const int nr_bits_per_code = 5, nr_codes = 32, nr_bits_max = 80;
	const int shift_down = 27, shift_up = 31;
	char down_shift_chars[nr_codes + 1], up_shift_chars[nr_codes + 1];
	gets(down_shift_chars);
	gets(up_shift_chars);
	char bs[nr_bits_max + 1], ms[nr_bits_max / nr_bits_per_code + 1];
	while (gets(bs)) {
		bool up_shift = false;
		int length = 0;
		for (const char* p = bs; *p; ) {
			int code = 0;
			for (int i = 0; i < nr_bits_per_code; i++, p++) {
				code <<= 1;
				code |= *p - '0';
			}
			if (code == shift_down)
				up_shift = false;
			else if (code == shift_up)
				up_shift = true;
			else
				ms[length++] = (up_shift) ? up_shift_chars[code] : down_shift_chars[code];
		}
		ms[length] = '\0';
		printf("%s\n", ms);
	}
	return 0;
}

