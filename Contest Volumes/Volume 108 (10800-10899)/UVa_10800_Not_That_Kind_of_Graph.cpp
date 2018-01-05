
/*
	UVa 10800 - Not That Kind of Graph

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10800_Not_That_Kind_of_Graph.cpp
*/

#include <cstdio>

int main()
{
	int n;
	scanf("%d", &n);
	for (int case_nr = 1; case_nr <= n; case_nr++) {
		const int nr_states_max = 50;
		char states[nr_states_max + 3];
		scanf("%s", &states[2]);
		int width = 2;
		int prices[nr_states_max + 2];
		int p = 0, min_p = nr_states_max + 1;
		for (const char* ps = states + 2; *ps; ps++) {
			switch (*ps) {
			case 'R':
				prices[width++] = p++;
				break;
			case 'F':
				prices[width++] = --p;
				if (p < min_p)
					min_p = p;
				break;
			case 'C':
				prices[width++] = p;
				break;
			}
		}
		if (min_p < 0)
			for (int x = 2; x < width; x++)
				prices[x] -= min_p;
		int height = 0;
		for (int x = 2; x < width; x++)
			if (height < prices[x] + 1)
				height = prices[x] + 1;
		printf("Case #%d:\n", case_nr);
		for (int y = 0; y < height; y++) {
			char line[nr_states_max + 3];
			line[0] = '|'; line[1] = ' ';
			int max_x = 0;
			for (int x = 2; x < width; x++) {
				if (prices[x] == height - 1 - y) {
					switch (states[x]) {
					case 'R':
						line[x] = '/'; break;
					case 'F':
						line[x] = '\\'; break;
					case 'C':
						line[x] = '_'; break;
					}
					max_x = x;
				}
				else
					line[x] = ' ';
			}
			line[max_x + 1] = '\0';
			puts(line);
		}
		char x_axis[nr_states_max + 4];
		x_axis[0] = '+'; x_axis[1] = '-';
		for (int x = 2; x <= width; x++)
			x_axis[x] = '-';
		x_axis[width + 1] = '\0';
		puts(x_axis);
		putchar('\n');
	}
	return 0;
}

