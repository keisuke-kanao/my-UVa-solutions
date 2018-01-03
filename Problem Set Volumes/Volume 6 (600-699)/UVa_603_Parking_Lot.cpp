
/*
	UVa 603 - Parking Lot

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_603_Parking_Lot.cpp
*/

#include <cstdio>

const int nr_cars_max = 20;

struct car {
	int original_, parked_, current_;
} cars[nr_cars_max + 1];

int main()
{
	int nr_sets;
	scanf("%d", &nr_sets);
	getchar();
	getchar(); // skip a blank line
	while (nr_sets--) {
		int nr_cars;
		for (nr_cars = 0; ; nr_cars++) {
			car& c = cars[nr_cars];
			scanf("%d", &c.original_);
			if (c.original_ == 99)
				break;
			c.parked_ = 0;
			c.current_ = c.original_;
		}
		getchar();
		while (true) {
			int cc;
			if ((cc = getchar()) == '\n' || cc == EOF)
				break;
			ungetc(cc, stdin);
			int p;
			scanf("%d", &p);
			getchar();
			int min_d = nr_cars_max + 1, min_i;
			for (int i = 0; i < nr_cars; i++) {
				car& c = cars[i];
				if (!c.parked_) {
					int d = p - c.current_;
					if (d < 0)
						d += nr_cars_max;
					if (d < min_d) {
						min_d = d; min_i = i;
					}
				}
			}
			for (int i = 0; i < nr_cars; i++) {
				car& c = cars[i];
				if (!c.parked_) {
					c.current_ += min_d;
					if (c.current_ > nr_cars_max)
						c.current_ -= nr_cars_max;
					if (i == min_i)
						c.parked_ = c.current_;
				}
			}
		}
		for (int i = 0; i < nr_cars; i++) {
			const car& c = cars[i];
			if (c.parked_)
				printf("Original position %d parked in %d\n", c.original_, c.parked_);
			else
				printf("Original position %d did not park\n", c.original_);
		}
		if (nr_sets)
			putchar('\n');
	}
	return 0;
}

