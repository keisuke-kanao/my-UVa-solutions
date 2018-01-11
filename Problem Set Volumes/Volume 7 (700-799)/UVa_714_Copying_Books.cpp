
/*
	UVa 714 - Copying Books

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_714_Copying_Books.cpp
*/

#include <algorithm>
#include <limits>
#include <cstdio>
using namespace std;

const int MAXN = 500; // largest number of books
const int MAXK = 500; // largest number of dividers

long long pages[MAXN + 1];
long long prefix_sums[MAXN + 1]; // prefix sums array
long long min_pages[MAXN + 1][MAXK + 1];
int min_dividers[MAXN + 1][MAXK + 1];

int dividers_positions[MAXK + 1] = {0};
	// dividers_positions[i] is the i-th divider's position
long long sum_of_pages[MAXN + 1];
	// sum_of_pages[i] is the sum of pages between the (i - 1)-th devider and i-th divider

void read_partition(int* n, int* k)
{
	scanf("%d %d", n, k);
	for (int i = 1; i <= *n; i++)
		scanf("%lld", &pages[i]);
}

#ifdef DEBUG

void print_min_pages(int n, int k)
{
	putchar('\n');
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= k; j++) 
			printf(" %lld ", min_pages[i][j]);
		putchar('\n');
	}
}

void print_min_dividers(int n, int k)
{
	putchar('\n');
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= k; j++) 
			printf(" %d ", min_dividers[i][j]);
		putchar('\n');
	}
}

#endif // DEBUG

void calculate_sum_of_pages(int start, int end, int dividers, int& divided)
{
	long long sum = 0;
	for (int i = start; i <= end; i++) {
		if (divided < dividers - 1 && i < end) {
			++divided;
			dividers_positions[divided] = i;
			sum_of_pages[divided] = pages[i];
		}
		else
			sum += pages[i];
	}
	if (sum) {
		++divided;
		dividers_positions[divided] = end;
		sum_of_pages[divided] = sum;
	}
}

void reconstruct_partition(int n, int k, int dividers, int& divided)
{
	if (k == 1)
		calculate_sum_of_pages(1, n, dividers, divided);
	else {
		reconstruct_partition(min_dividers[n][k], k - 1, dividers - 1, divided);
		calculate_sum_of_pages(min_dividers[n][k] + 1, n, dividers, divided);
	}
}

void adjust_partition(int i, long long max_page)
{
	bool adjusted = false;
	while (/* sum_of_pages[i] > sum_of_pages[i + 1] && */ dividers_positions[i - 1] + 1 < dividers_positions[i] &&
		sum_of_pages[i + 1] + pages[dividers_positions[i]] <= max_page) {
		adjusted = true;
		sum_of_pages[i] -= pages[dividers_positions[i]];
		sum_of_pages[i + 1] += pages[dividers_positions[i]];
		dividers_positions[i]--;
	}
	if (adjusted && i > 1)
		adjust_partition(i - 1, max_page);
}

void partition(int n, int k)
{
	// construct the prefix sums
	prefix_sums[0] = 0;
	int i, j, x;
	for (i = 1; i <= n; i++)
		prefix_sums[i] = prefix_sums[i - 1] + pages[i];
	// initialize the boundaries
	for (i = 1; i <= n; i++)
		min_pages[i][1] = prefix_sums[i];
	for (int j = 1; j <= k; j++)
		min_pages[1][j] = pages[1];
	// evaluate the main recurrence
	for (i = 2; i <= n; i++)
		for (j = 2; j <= k; j++) {
			min_pages[i][j] = numeric_limits<int>::max();
			for (x = 1; x <= i - 1; x++) {
				long long cost = max(min_pages[x][j - 1], prefix_sums[i] - prefix_sums[x]);
				if (min_pages[i][j] > cost) {
					min_pages[i][j] = cost;
					min_dividers[i][j] = x;
				}
			}
		}
#ifdef DEBUG
	print_min_pages(n, k);
	print_min_dividers(n, k);
#endif
	int divided = 0;
	reconstruct_partition(n, k, k, divided); // print the book partition
	long long max_page = min_pages[n][k];
	for (i = 1; i < k; i++)
		adjust_partition(i, max_page);
	i = 1;
	for (int j = 1; j <= k; j++) {
		for ( ; i <= dividers_positions[j]; i++) {
			if (i > 1)
				putchar(' ');
			printf("%lld", pages[i]);
		}
		if (j < k)
			printf(" /");
	}
	putchar('\n');
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		int n; // number of books
		int k; // number of scribers
		read_partition(&n, &k);
		partition(n, k);
	}
	return 0;
}

