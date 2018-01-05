
/*
	UVa 10473 - Simple Base Conversion

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10473_Simple_Base_Conversion.cpp
*/

#include <cstdio>
#include <cstdlib>
using namespace std;

int main()
{
	while (true) {
		char number[16];
		scanf("%s", number);
		if (number[0] == '0' && number[1] == 'x')
			printf("%d\n", strtol(number, NULL, 16));
		else {
			int n = strtol(number, NULL, 10);
			if (n < 0)
				break;
			else
				printf("0x%X\n", n);
		}
	}
	return 0;
}

