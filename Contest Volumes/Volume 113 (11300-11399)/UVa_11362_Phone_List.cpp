
/*
	UVa 11362 - Phone List

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11362_Phone_List.cpp
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

const int n_max = 10000, nr_digits_max = 10;

char phone_numbers[n_max][nr_digits_max + 1];

int compare_phone_number(const void* i, const void* j)
{
	return strcmp(reinterpret_cast<const char*>(i), reinterpret_cast<const char*>(j));
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%s", phone_numbers[i]);
		qsort(phone_numbers, n, nr_digits_max + 1, compare_phone_number);
		bool yes = true;
		for (int i = 0; i < n - 1; i++)
			if (!strncmp(phone_numbers[i], phone_numbers[i + 1], strlen(phone_numbers[i]))) {
				yes = false; break;
			}
		printf("%s\n", ((yes) ? "YES" : "NO"));
	}
	return 0;
}

