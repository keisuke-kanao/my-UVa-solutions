
/*
	UVa 272 - TEX Quotes

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_272_TEX_Quotes.cpp
*/

#include <cstdio>
using namespace std;

int main()
{
	bool inquate = false;
	char c;
	while ((c = getchar()) != EOF) {
		if (c == '"') {
			if (inquate)
				printf("''");
			else
				printf("``");
			inquate = !inquate;
		}
		else
			putchar(c);
	}
	return 0;
}

