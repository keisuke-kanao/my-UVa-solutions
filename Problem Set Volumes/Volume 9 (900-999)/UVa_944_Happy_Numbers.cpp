
/*
	UVa 944 - Happy Numbers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_944_Happy_Numbers.cpp
*/

#include <cstdio>
#include <cstring>

const int n_max = 99999, sum_of_squares_max = 405;

enum {unknown, happy, unhappy};

struct happy_number {
	int happy_; // 0 for unknown, 1 for happy, 2 for unhappy
	int nr_iterations_;
} happy_numbers[n_max + 1];

int sum_of_squares[sum_of_squares_max + 1]; // sum_of_squares[i] is the number whose sum of squares is i

int calculate_sum_of_squares(int n)
{
	int d, s = 0;
	do {
		d = n % 10;
		s += d * d;
		n /= 10;
	} while (n);
	return s;
}

void set_happy_numbers(int number, int nr_iterations)
{
	do {
		happy_numbers[number].happy_ = happy;
		happy_numbers[number].nr_iterations_ = nr_iterations++;
		number = sum_of_squares[number];
	} while (number != -1);
}

void set_unhappy_numbers(int number)
{
	do {
		happy_numbers[number].happy_ = unhappy;
		number = sum_of_squares[number];
	} while (number != -1);
}

int main()
{
	int n;
	for (n = 1; n <= sum_of_squares_max; n++) {
		if (happy_numbers[n].happy_ == unknown) {
			int m = n;
			memset(sum_of_squares, 0, sizeof(sum_of_squares));
			sum_of_squares[m] = -1;
			while (true) {
				int s = calculate_sum_of_squares(m);
				if (s == 1 || happy_numbers[s].happy_ == happy) {
					set_happy_numbers(m, happy_numbers[s].nr_iterations_ + 1);
					break;
				}
				else if (sum_of_squares[s] || happy_numbers[s].happy_ == unhappy) {
					set_unhappy_numbers(m);
					break;
				}
				sum_of_squares[s] = m;
				m = s;
			}
		}
#ifdef DEBUG
		if (happy_numbers[n].happy_ == happy)
			printf("%d %d\n", n, happy_numbers[n].nr_iterations_);
#endif
	}
	for ( ; n <= n_max; n++) {
		int s = calculate_sum_of_squares(n);
		if (happy_numbers[s].happy_ == happy) {
			happy_numbers[n].happy_ = happy;
			happy_numbers[n].nr_iterations_ = happy_numbers[s].nr_iterations_ + 1;
#ifdef DEBUG
			printf("%d %d\n", n, happy_numbers[n].nr_iterations_);
#endif
		}
		else
			happy_numbers[n].happy_ = unhappy;
	}
	bool printed = false;
	int l, h;
	while (scanf("%d %d", &l, &h) != EOF) {
		if (printed)
			putchar('\n');
		else
			printed = true;
		for (n = l; n <= h; n++)
			if (happy_numbers[n].happy_ == happy)
				printf("%d %d\n", n, happy_numbers[n].nr_iterations_);
	}
	return 0;
}

