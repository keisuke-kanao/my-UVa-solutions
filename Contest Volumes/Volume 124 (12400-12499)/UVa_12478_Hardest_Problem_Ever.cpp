
/*
	UVa 12478 - Hardest Problem Ever (Easy)

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12478_Hardest_Problem_Ever.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const char* names[] = {
	"RAKIBUL", "ANINDYA", "MOSHIUR", "SHIPLU", "KABIR", "SUNNY", "OBAIDA", "WASI"
};

const int nr_rows = 9, nr_columns = 9;

const char grid[nr_rows][nr_columns] = {
	{'O', 'B', 'I', 'D', 'A', 'I', 'B', 'K', 'R'},
	{'R', 'K', 'A', 'U', 'L', 'H', 'I', 'S', 'P'},
	{'S', 'A', 'D', 'I', 'Y', 'A', 'N', 'N', 'O'},
	{'H', 'E', 'I', 'S', 'A', 'W', 'H', 'I', 'A'},
	{'I', 'R', 'A', 'K', 'I', 'B', 'U', 'L', 'S'},
	{'M', 'F', 'B', 'I', 'N', 'T', 'R', 'N', 'O'},
	{'U', 'T', 'O', 'Y', 'Z', 'I', 'F', 'A', 'H'},
	{'L', 'E', 'B', 'S', 'Y', 'N', 'U', 'N', 'E'},
	{'E', 'M', 'O', 'T', 'I', 'O', 'N', 'A', 'L'}
};

#ifdef DEBUG
bool search_name(const char* name, int length)
{
	for (int r = 0; r < nr_rows; r++)
		for (int c = 0; c <= nr_columns - length; c++) {
			int ci;
			for (ci = 0; ci < length; ci++)
				if (name[ci] != grid[r][c + ci])
					break;
			if (ci == length) {
				printf("  horozontal %d %d: %s\n", r, c, name);
				return true;
			}
		}
	for (int r = 0; r <= nr_rows - length; r++)
		for (int c = 0; c < nr_columns; c++) {
			int ri;
			for (ri = 0; ri < length; ri++)
				if (name[ri] != grid[r + ri][c])
					break;
			if (ri == length) {
				printf(" vertical    %d %d: %s\n", r, c, name);
				return true;
			}
		}
	return false;
}
#endif

int main()
{
#ifdef DEBUG
	for (size_t i = 0; i < sizeof(names) / sizeof(const char*); i++) {
		char name[8];
		strcpy(name, names[i]);
		puts(name);
		int length = strlen(name);
		sort(name, name + length);
		int nr_found = 0;
		do {
			if (search_name(name, length)) {
				if (++nr_found == 2)
					break;
			}
		} while (next_permutation(name, name + length));
/*
		if (nr_found == 2) {
			puts(names[i]);
			break;
		}
*/
	}
#else
	puts(names[4]);
#endif
	return 0;
}

