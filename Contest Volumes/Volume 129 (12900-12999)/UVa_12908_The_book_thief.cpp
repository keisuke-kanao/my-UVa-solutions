
/*
	UVa 12908 - The book thief

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_12908_The_book_thief.cpp
*/

#include <cstdio>
#include <cmath>

int main()
{
	while (true) {
		int s;
		scanf("%d", &s);
		if (!s)
			 break;
		int n = static_cast<int>(ceil((-1.0 + sqrt(1.0 + 8.0 * s)) / 2.0));
		if (n * (n + 1) / 2 == s)
			n++;
		printf("%d %d\n", n * (n + 1) / 2 - s, n);
	}
	return 0;
}

