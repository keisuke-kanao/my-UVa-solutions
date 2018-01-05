
/*
	UVa 10851 - 2D Hieroglyphs decoder

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10851_2D_Hieroglyphs_decoder.cpp
*/

#include <cstdio>
#include <cstring>

int main()
{
	int N;
	scanf("%d", &N);
	while (N--) {
		const int message_length_max = 80;
		char s[message_length_max + 3], message[message_length_max + 1];
		scanf("%s", s);
		int message_length = strlen(s) - 2;
		memset(message, 0, message_length + 1);
		for (int i = 0, b = 1; i < 8; i++, b <<= 1) {
			scanf("%s", s);
			for (int j = 0; j < message_length; j++)
				if (s[j + 1] == '\\')
					message[j] |= b;
		}
		scanf("%s", s);
		printf("%s\n", message);
	}
	return 0;
}

