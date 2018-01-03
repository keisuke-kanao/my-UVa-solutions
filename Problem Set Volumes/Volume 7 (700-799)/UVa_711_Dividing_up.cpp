
/*
	UVa 711 - Dividing up

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_711_Dividing_up.cpp

	from Mid-Central European Regional Contest 1999
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_MCRC/1999/index.html)
*/

#include <cstdio>

/*
Some of the previous posts only made things more confusing, so let me try to summarize all the hints so far:
(1) You are likely to get TLE with a straightforward Dynamic Programming solution. 
  You need to reduce the number of balls intelligently.
(2) The strategy for reducing 1,2,3 balls is very simple. 
  Basically reduce {1,1} to {2} whenever you have at least three 1-balls. Similarly for the 2-balls and 3-balls.
(3) The strategy for reducing 4,5 balls are pretty much the same. 
  You want to reduce both 4-balls and 5-balls to 6-balls. 
  When you reduce 4-balls, you need to make sure the number of 4-balls you reduce and 
  the number of 6-balls you reducing to are both even. 
  For instance, reducing {4,4,4} to {6,6} would be wrong. 
  You also need to figure out at least how many 4-balls you will need before you can reduce them.
(4) Finally, you also need to reduce the number of 6-balls. 
  You know if both sides have at least one 6-ball, then you could have safely removed both 6-balls at the beginning. 
  So the only time you can't reduce 6-balls is when all the 6-balls are used to "balance" the sum of the rest of the balls. 
  So you need to figure out the C in the equation 6*C >= 5*n[5] + 4*n[4] + 3*n[3] + 2*n[2] + n[1]
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstring>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int nr_values = 6, nr_marbles_max = 20000;
int marbles[nr_values + 1];
char values[nr_values * nr_marbles_max + 1];

bool dividing_up(int s)
{
#ifdef DEBUG
	printf("%d\n", s);
#endif
	if (s & 1)
		return false;
	int m;
	if (marbles[1] > 2) { // reduce 2 1-marbles to 1 2-marble
		m = (marbles[1] - 1) / 2;
		marbles[1] = marbles[1] - m * 2;
		marbles[2] += m;
	}
	if (marbles[2] > 2) { // reduce 2 2-marbles to 1 4-marble
		m = (marbles[2] - 1) / 2;
		marbles[2] = marbles[2] - m * 2;
		marbles[4] += m;
	}
	if (marbles[3] > 2) { // reduce 2 3-marbles to 1 6-marble
		m = (marbles[3] - 1) / 2;
		marbles[3] = marbles[3] - m * 2;
		marbles[6] += m;
	}
/*
	if (marbles[4] > 6) { // reduce 6 4-marbles to 4 6-marbles
		m = (marbles[4] - 5) / 6;
		marbles[4] = marbles[4] - m * 6;
		marbles[6] += m * 4;
	}
	if (marbles[5] > 12) { // reduce 12 5-marbles to 10 6-marbles
		m = (marbles[5] - 11) / 12;
		marbles[5] = marbles[5] - m * 12;
		marbles[6] += m * 10;
	}
*/
	s = 0;
	for (int i = 1; i < nr_values; i++)
		s += i * marbles[i];
/*
	m = (s + 5) / 6; // number of 6-marbles that may be used to balance the sum of other marbles
	if (marbles[6] - m > 1)
		marbles[6] = m + (marbles[6] - m) % 2;
*/
	s += 6 * marbles[6];
#ifdef DEBUG
	for (int i = 1; i <= nr_values; i++)
		printf("%d%c", marbles[i], ((i < nr_values) ? ' ' : '\n'));
#endif
	int hs = s / 2;
	memset(values, 0, s + 1);
	s = 0;
	for (int i = 1; i <= nr_values; i++)
		for (int j = 0; j < marbles[i]; j++) {
			for (int k = s; k; k--) {
				values[k + i] |= values[k];
				if (values[hs])
					return true;
			}
			values[i] = 1;
			s += i;
/*
#ifdef DEBUG
			for (int k = 1; k <= s; k++)
				if (values[k])
					printf("%d ", k);
			putchar('\n');
#endif
*/
		}
	return false;
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	for (int c = 1; ; c++) {
		int s = 0;
		for (int i = 1; i <= nr_values; i++) {
			scanf("%d", &marbles[i]);
			s += i * marbles[i];
		}
		if (!s)
			break;
		printf("Collection #%d:\n", c);
		puts((dividing_up(s)) ? "Can be divided.\n" : "Can't be divided.\n");
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}

