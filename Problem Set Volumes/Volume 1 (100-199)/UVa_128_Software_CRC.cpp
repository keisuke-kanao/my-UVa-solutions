
/*
	UVa 128 - Software CRC

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_128_Software_CRC.cpp
*/

#include <cstdio>

unsigned int calculate_crd(const char* line)
{
	unsigned int g = 34943;
	unsigned int remainder = 0;
	for ( ; *line; line++, remainder <<= 8) {
		remainder |= *line;
		remainder %= g;
	}
	remainder <<= 8;
	unsigned int crc = 0;
	if (remainder % g) {
		unsigned int quotient = remainder / g;
		crc = g * (quotient + 1) & 0xffff;
	}
	return crc;
}

int main()
{
	while (true) {
		const int nr_chrs_max = 1024;
		char line[nr_chrs_max + 1];
		gets(line);
		if (line[0] == '#')
			break;
		unsigned int crc = calculate_crd(line);
		printf("%02X %02X\n", (crc & 0xff00) >> 8, crc & 0xff);
	}
	return 0;
}

