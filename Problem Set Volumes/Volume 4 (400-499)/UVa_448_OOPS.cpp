
/*
	UVa 448 - OOPS!

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_448_OOPS.cpp
*/

#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;

const char* opcodes[] = {
	"ADD", "SUB", "MUL", "DIV",	"MOV", "BREQ", "BRLE", "BRLS",
	"BRGE", "BRGR", "BRNE", "BR", "AND", "OR", "XOR", "NOT"
};

const int nr_operand_digits = 4;
const int nr_digits_max = 30 + nr_operand_digits - 1;
int idigits, nr_digits;
char digits[nr_digits_max + 1];

int get_opcode()
{
	if (idigits == nr_digits) {
		if (!gets(digits))
			return -1;
		idigits = 0;
		nr_digits = strlen(digits);
	}
	char c = digits[idigits++];
	if (isdigit(c))
		return c - '0';
	else
		return c - 'A' + 10;
}

int get_operand()
{
	if (idigits + nr_operand_digits > nr_digits) {
		memcpy(digits, digits + idigits, nr_digits - idigits);
		gets(digits + nr_digits - idigits);
		idigits = 0;
		nr_digits = strlen(digits);
	}
	int opr = 0;
	for (int i = 0; i < nr_operand_digits; i++, idigits++) {
		if (i)
			opr <<= 4;
		char c = digits[idigits];
		if (isdigit(c))
			opr += c - '0';
		else
			opr += c - 'A' + 10;
	}
	return opr;
}

void print_operand(int opr)
{
	int mode = (opr & 0xe000) >> 14, value = opr & 0x3fff;
	switch (mode) {
	case 0:
		printf("R%d", value); break;
	case 1:
		printf("$%d", value); break;
	case 2:
		printf("PC+%d", value); break;
	case 3:
		printf("%d", value); break;
	}
}

int main()
{
	int opc;
	while ((opc = get_opcode()) != -1) {
		printf("%s ", opcodes[opc]);
		print_operand(get_operand());
		if (opc <= 4 || opc >= 12 && opc <= 14) {
			putchar(',');
			print_operand(get_operand());
			if (opc >= 12 && opc <= 14) {
				putchar(',');
				print_operand(get_operand());
			}
		}
		putchar('\n');
	}
	return 0;
}

