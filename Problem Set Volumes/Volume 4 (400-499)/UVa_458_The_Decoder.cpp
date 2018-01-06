
/*
	UVa 458 - The Decoder

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_458_The_Decoder.cpp
*/

/*
	This is a problem of ROT (Caesar) Cipher whose shift is 7.
*/

#include <iostream>
#include <string>
using namespace std;

int main(int /* argc */, char** /* argv */)
{
	string s;
	while (getline(cin, s)) {
		for (int i = 0, l = s.length(); i < l; i++)
			s[i] -= 7;
		cout << s << endl;
	}
	return 0;
}

