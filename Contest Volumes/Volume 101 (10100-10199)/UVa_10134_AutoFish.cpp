
/*
	UVa 10134 - AutoFish

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10134_AutoFish.cpp
*/

#include <cstdio>

int main()
{
	int nr_cases;
	scanf("%d", &nr_cases);
	while (getchar() != '\n')
		;
	getchar();
	while (nr_cases--) {
		char instruction[8];
		int nr_executed = 0, nr_caught = 0, nr_last_fish = 0, nr_bait_instructions = 0, nr_bait_units = 0;
		while (gets(instruction) && instruction[0]) {
			nr_executed++;
			switch (instruction[0]) {
			case 'f': // "fish"
				if (nr_bait_units) {
					nr_last_fish++;
					if (!nr_caught || // the first fish caught
						nr_executed  >= 7 && nr_last_fish >= 3) {
						nr_caught++;
						nr_bait_units--;
						nr_executed = nr_last_fish = 0;
					}
				}
				break;
			case 'b': // "bait"
				if (nr_bait_units < 3) {
					if (++nr_bait_instructions == 2) {
						nr_bait_instructions = 0;
						nr_bait_units++;
					}
				}
				break;
			default: // "lunch"
				break;
			}
		}
		printf("%d\n", nr_caught);
		if (nr_cases)
			putchar('\n');
	}
	return 0;
}

