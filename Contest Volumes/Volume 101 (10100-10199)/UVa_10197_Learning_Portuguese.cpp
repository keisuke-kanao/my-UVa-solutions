
/*
	UVa 10197 - Learning Portuguese

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10197_Learning_Portuguese.cpp

	An accepted solution.
*/

#include <cstdio>
#include <cstring>

const int nr_chars_max = 30;

enum {unknown_conjugation, first_conjugation, second_conjugation, third_conjugation};
const char* pronouns[] = {"eu", "tu", "ele/ela", "n\xf3s", "v\xf3s", "eles/elas"};

int get_conjugation(const char* v, int length, char* root, char& tv)
{
	int conjugation = unknown_conjugation;
	if (length > 1) {
		if (!strcmp(&v[length - 2], "ar"))
			conjugation = first_conjugation;
		else if (!strcmp(&v[length - 2], "er"))
			conjugation = second_conjugation;
		else if (!strcmp(&v[length - 2], "ir"))
			conjugation = third_conjugation;
	}
	if (conjugation != unknown_conjugation) {
		strncpy(root, v, length - 2); root[length - 2] = '\0';
		tv = v[length - 2];
	}
	return conjugation;
}

void print_1st_or_2nd_conjugation(const char* root, char tv)
{
	printf("%-10s%so\n", pronouns[0], root);
	printf("%-10s%s%cs\n", pronouns[1], root, tv);
	printf("%-10s%s%c\n", pronouns[2], root, tv);
	printf("%-10s%s%cmos\n", pronouns[3], root, tv);
	printf("%-10s%s%cis\n", pronouns[4], root, tv);
	printf("%-10s%s%cm\n", pronouns[5], root, tv);
}

void print_3rd_conjugation(const char* root, char tv)
{
	printf("%-10s%so\n", pronouns[0], root);
	printf("%-10s%ses\n", pronouns[1], root);
	printf("%-10s%se\n", pronouns[2], root);
	printf("%-10s%s%cmos\n", pronouns[3], root, tv);
	printf("%-10s%s%cs\n", pronouns[4], root, tv);
	printf("%-10s%sem\n", pronouns[5], root);
}

int main()
{
	bool printed = false;
	char v1[nr_chars_max + 1], v2[nr_chars_max + 1];
	while (scanf("%s %s", v1, v2) != EOF) {
		if (printed)
			putchar('\n');
		printf("%s (to %s)\n", v1, v2);
		int v1_length = strlen(v1);
		char root[nr_chars_max + 1], tv;
		switch (get_conjugation(v1, v1_length, root, tv)) {
		case first_conjugation: case second_conjugation:
			print_1st_or_2nd_conjugation(root, tv);
			break;
		case third_conjugation:
			print_3rd_conjugation(root, tv);
			break;
		default:
			puts("Unknown conjugation");
			break;
		}
		printed = true;
	}
	return 0;
}

