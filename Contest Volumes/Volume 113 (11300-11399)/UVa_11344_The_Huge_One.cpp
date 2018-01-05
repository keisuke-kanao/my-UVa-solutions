
/*
	UVa 11344 - The Huge One

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11344_The_Huge_One.cpp
*/

#include <cstdio>
#include <cstring>

bool is_multiple_of_1(const char* number, int length)
{
	return true;
}

bool is_multiple_of_2(const char* number, int length)
{
	return ((number[length - 1] - '0') % 2) ? false : true;
}

bool is_multiple_of_3(const char* number, int length)
{
	int s = 0;
	for (int i = 0; i < length; i++)
		s += number[i] - '0';
	return (s % 3) ? false : true;
}

bool is_multiple_of_4(const char* number, int length)
{
	int s = number[length - 1] - '0';
	if (length > 1)
		s += (number[length - 2] - '0') * 10;
	return (s % 4) ? false : true;
}

bool is_multiple_of_5(const char* number, int length)
{
	return ((number[length - 1] - '0') % 5) ? false : true;
}

bool is_multiple_of_6(const char* number, int length)
{
	return is_multiple_of_2(number, length) && is_multiple_of_3(number,length);
}

bool is_multiple_of_7(const char* number, int length)
{
	int s = 0;
	for (int i = 0, j = length - 1; j >= 0; i++) {
		int k = number[j--] - '0';
		if (j >= 0)
			k += (number[j--] - '0') * 10;
		if (j >= 0)
			k += (number[j--] - '0') * 100;
		if (i & 1)
			s -= k;
		else
			s += k;
	}
	return (s % 7) ? false : true;
}

bool is_multiple_of_8(const char* number, int length)
{
	int s = number[length - 1] - '0';
	if (length > 1) {
		s += (number[length - 2] - '0') * 10;
		if (length > 2)
			s += (number[length - 3] - '0') * 100;
	}
	return (s % 8) ? false : true;
}

bool is_multiple_of_9(const char* number, int length)
{
	int s = 0;
	for (int i = 0; i < length; i++)
		s += number[i] - '0';
	return (s % 9) ? false : true;
}

bool is_multiple_of_10(const char* number, int length)
{
	return number[length - 1] == '0';
}

bool is_multiple_of_11(const char* number, int length)
{
	int s = 0;
	for (int i = 0, j = length - 1; j >= 0; i++, j--) {
		int k = number[j] - '0';
		if (i & 1)
			s -= k;
		else
			s += k;
	}
	return (s % 11) ? false : true;
}

bool is_multiple_of_12(const char* number, int length)
{
	return is_multiple_of_3(number, length) && is_multiple_of_4(number, length);
}

int main()
{
	typedef bool (*IS_MULTIPLE_OF_N_FUNCTION)(const char* number, int length);
	const IS_MULTIPLE_OF_N_FUNCTION is_multiple_of_n_functions[] = {
		NULL,
		is_multiple_of_1, is_multiple_of_2, is_multiple_of_3, is_multiple_of_4, is_multiple_of_5, is_multiple_of_6,
		is_multiple_of_7, is_multiple_of_8, is_multiple_of_9, is_multiple_of_10, is_multiple_of_11, is_multiple_of_12
	};

	int N;
	scanf("%d", &N);
	while (N--) {
		const int M_digits_max = 1001;
		char M[M_digits_max + 1];
		scanf("%s", M);
		int length = strlen(M), S;
		scanf("%d", &S);
		bool wonderful = true;
		while (S--) {
			int number;
			scanf("%d", &number);
			if (wonderful && !is_multiple_of_n_functions[number](M, length))
				wonderful = false;
		}
		printf("%s - %s.\n", M, ((wonderful) ? "Wonderful" : "Simple"));
	}
	return 0;
}

