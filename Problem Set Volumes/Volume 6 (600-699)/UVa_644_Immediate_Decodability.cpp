
/*
	UVa 644 - Immediate Decodability

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_644_Immediate_Decodability.cpp
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct symbol
{
	int length_;
	int code_;
	symbol() : length_(-1), code_(0) {}
	symbol(int length, int code) : length_(length), code_(code) {}
	bool operator<(const symbol& s) const {return length_ < s.length_;}
};

bool is_immediate_decodable(int n, const symbol symbols[])
{
	int masks[] = {0x0000, 0x0001, 0x0003, 0x0007, 0x000f, 0x001f, 0x003f, 0x007f, 0x00ff, 0x01ff, 0x03ff};
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++) {
			int diff = symbols[i].code_ ^ symbols[j].code_;
			if (!(diff & masks[symbols[i].length_]))
				return false;
		}
	return true;
}

int main()
{
	const int nr_symbols_max = 8;
	string bc;
	for (int g = 1; cin >> bc; g++) {
		int nr_symbols = 0;
		symbol symbols[nr_symbols_max];
		do {
			int length = bc.length(), code = 0;
			for (int i = 0, b = 1; i < length; i++, b <<= 1)
				if (bc[i] == '1')
					code |= b;
			symbols[nr_symbols++] = symbol(length, code);
			cin >> bc;
		} while (bc != "9");
		sort(symbols, symbols + nr_symbols);
		cout << "Set " << g <<
			((is_immediate_decodable(nr_symbols, symbols)) ? " is immediately decodable\n" : " is not immediately decodable\n");
	}
	return 0;
}

