
/*
	UVa 445 - Marvelous Mazes

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_445_Marvelous_Mazes.cpp
*/

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
	string desc;
	while (getline(cin, desc)) {
		if (desc.empty())
			cout << endl;
		else {
			int n = 0;
			for (int i = 0, e = desc.length(); i < e; i++) {
				char c = desc[i];
				if (isdigit(c))
					n += c - '0';
				else {
					switch (c) {
					case 'b':
						while (n--)
							cout << ' ';
						break;
					case '!':
						cout << endl;
						break;
					default:
						while (n--)
							cout << c;
						break;
					}
					n = 0;
				}
			}
			cout << endl;
		}
	}
	return 0;
}

