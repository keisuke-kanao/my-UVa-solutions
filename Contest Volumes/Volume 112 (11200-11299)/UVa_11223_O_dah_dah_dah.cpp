
/*
	UVa 11223 - O: dah dah dah!

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_11223_O_dah_dah_dah.cpp
*/

#include <map>
#include <cstdio>
#include <cstring>
using namespace std;

pair<char, const char*> symbol_codes[] = {
	make_pair('A', ".-"),	make_pair('J', ".---"),	make_pair('S', "..."),		make_pair('1', ".----"),	make_pair('.', ".-.-.-"),	make_pair(':', "---..."),
	make_pair('B', "-..."),	make_pair('K', "-.-"),	make_pair('T', "-"),		make_pair('2', "..---"), 	make_pair(',', "--..--"),	make_pair(';', "-.-.-."),
	make_pair('C', "-.-."),	make_pair('L', ".-.."), make_pair('U', "..-"),		make_pair('3', "...--"),	make_pair('?', "..--.."),	make_pair('=', "-...-"),
	make_pair('D', "-.."),	make_pair('M', "--"),	make_pair('V', "...-"),		make_pair('4', "....-"),	make_pair('\'', ".----."),	make_pair('+', ".-.-."),
	make_pair('E', "."),	make_pair('N', "-."),	make_pair('W', ".--"),		make_pair('5', "....."),	make_pair('!', "-.-.--"),	make_pair('-', "-....-"),
	make_pair('F', "..-."),	make_pair('O', "---"),	make_pair('X', "-..-"),		make_pair('6', "-...."),	make_pair('/', "-..-."),	make_pair('_', "..--.-"),
	make_pair('G', "--."),	make_pair('P', ".--."),	make_pair('Y', "-.--"),		make_pair('7', "--..."),	make_pair('(', "-.--."),	make_pair('"', ".-..-."),
	make_pair('H', "...."),	make_pair('Q', "--.-"),	make_pair('Z', "--.."),		make_pair('8', "---.."),	make_pair(')', "-.--.-"),	make_pair('@', ".--.-."),
	make_pair('I', ".."),	make_pair('R', ".-."),	make_pair('0', "-----"),	make_pair('9', "----."),	make_pair('&', ".-...")
};

struct code {
	const char* p_;

	code(const char* p) : p_(p) {}
	bool operator<(const code& c) const {return strcmp(p_, c.p_) < 0;}
};

int main()
{
	map<code, char> code_symbols;
	for (size_t i = 0, s = sizeof(symbol_codes) / sizeof(pair<char, const char*>); i < s; i++)
		code_symbols.insert(make_pair(code(symbol_codes[i].second), symbol_codes[i].first));

	int t;
	scanf("%d", &t);
	getchar();
	const int nr_chars_max = 2000;
	char s[nr_chars_max + 1];
	for (int m = 1; m <= t; m++) {
		gets(s);
		printf("Message #%d\n", m);
		char *p = s, *q = s;
		for ( ; *p; p++) {
			if (*p == ' ') {
				if (p > s && !*(p - 1)) // double silence
					putchar(' ');
				else { // simple silence
					*p = '\0';
					if (p - q)
						putchar(code_symbols[code(q)]);
				}
				q = p + 1;
			}
		}
		if (p - q)
			putchar(code_symbols[code(q)]);
		putchar('\n');
		if (m < t)
			putchar('\n');
	}
	return 0;
}

