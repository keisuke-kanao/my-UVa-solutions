
/*
	UVa 11483 - Code Creator

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11483_Code_Creator.cpp
*/

#include <cstdio>

int main()
{
	const char* prefix = "#include<string.h>\n#include<stdio.h>\nint main()\n{\n";
	const char* suffix = "printf(\"\\n\");\nreturn 0;\n}\n";
	const int nr_chars_max = 100;
	char s[nr_chars_max + 1];
	for (int cn = 1; ; cn++) {
		int n;
		scanf("%d", &n);
		getchar();
		if (!n)
			break;
		printf("Case %d:\n", cn);
		printf(prefix);
		while (true) {
			gets(s);
			const char* p = s;
			if (*p) {
				n--;
				printf("printf(\"");
				do {
					if (*p == '"' || *p == '\\')
						putchar('\\');
					putchar(*p++);
				} while (*p);
				printf("\\n\");\n");
			}
			if (!n)
				break;
		}
		printf(suffix);
	}
	return 0;
}

