
/*
	UVa 10222 - Decode the Mad man

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10222_Decode_the_Mad_man.cpp
*/

/*
	It is uncertain whether the leftmost two keys ('1', '2', 'q', 'w', 'a', 's', 'z', and 'x') are used in the encoded strings.
	Also, it is uncertain where the rightmost few keys ('\\' and '/') are assumed to be located in the "standard" keyboard.
*/

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

const char encoded_chars[] = "234567890-=`1ertyuiop[]\\qwdfghjkl;'ascvbnm,./zx";
const char decoded_chars[] = "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./";

int main()
{
	string s;
	while (getline(cin, s)) {
		for (const char* p = s.c_str(); *p; p++) {
			char c = static_cast<char>(tolower(*p));
			if (!isspace(c)) {
				int i = 0;
				for (int e = sizeof(encoded_chars); i < e; i++)
					if (encoded_chars[i] == c)
						break;
				c = decoded_chars[i];
			}
			cout << c;
		}
		cout << endl;
	}
	return 0;
}

