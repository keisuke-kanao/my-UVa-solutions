
/*
	UVa 702 - The Vindictive Coach

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_702_The_Vindictive_Coach.cpp

	An accepted solution.
*/

/*
a) If the captain is the shortest player on the team then 
  1) If he is the shortest player, then the order is obvious. 
  2) If there are two players total, then the second player goes next. 
  3) If there are three or more players, then the third shortest goes second in line so that the taller-shorter-taller... arrangement can be maintained 
     (so the third person in line will be the second shortest) 
*/

/*
LetÅfs think, We insert The first element in the array,M .
This number partition the remaining numbers into two parts
A-> The numbers less than M
B -> The number greater than M
After choosing the first element, We need to choose smaller number than M , 
so we can take any one element to be the inserted element.
and with this insertion we go to the next state where we need to choose from the higher elements,
Note That, which number is in the list doesÅft matter only the size of the partition and 
the move which we need to take.
*/

#include <cstdio>

const int N_max = 22;
long long nr_alignments[N_max][N_max][N_max];
	// nr_alignments[i][j][k] is the number of alignments at the i-th player 
	// with j players less than i-th player' number and k players greater than -i-th player's number

int main()
{
	int N, m;
	while (scanf("%d %d", &N, &m) != EOF) {
		if (N == 1) {
			puts("1");
			continue;
		}
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				for (int k = 0; k < N; k++)
					nr_alignments[i][j][k] = 0;
		int n = 0, less;
		if (m == 1) {
			n++;
			if (N > 2)
				nr_alignments[n][1][N - 3] = 1;
			else
				nr_alignments[n][0][0] = 1;
		}
		else
			nr_alignments[n][m - 1][N - m] = 1;
		for (n++, less = 1; n < N; n++, less = 1 - less) {
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++) {
					long long nr = nr_alignments[n - 1][i][j];
					if (nr) {
						if (less && i) {
							for (int ii = i - 1, jj = j; ii >= 0; ii--, jj++)
								nr_alignments[n][ii][jj] += nr;
						}
						else if (!less && j) {
							for (int ii = i, jj = j - 1; jj >= 0; ii++, jj--)
								nr_alignments[n][ii][jj] += nr;
						}
					}
				}
#ifdef DEBUG
			printf("%d\n  ", n);
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++) {
					long long nr = nr_alignments[n][i][j];
					if (nr)
						printf("[%d][%d]:%lld ", i, j, nr);
				}
			putchar('\n');
#endif
		}
		long long nr = 0;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				nr += nr_alignments[N - 1][i][j];
		printf("%lld\n", nr);
	}
	return 0;
}

/*
Sample Input

3 1
3 3
4 1

Sample Output

1
1
1

3 1
		1 3 2

														nr_of_		nr_of_
		less_than	greater_than	player				less_than	greater_than
		2							3					1			0
	>
									2					0			0

2 1
		less_than	greater_than	player				less_than	greater_than
									2					0			0

3 3
		3 1 2

4 1
		1 3 2 4

		less_than	greater_than	player				less_than	greater_than
		2			4				3					1			1
	>
					4				2					0			1
	<
									4					0			0

5 3
		3 1 4 2 5
		3 1 5 2 4
		3 2 4 1 5
		3 2 5 1 4
*/

/*
6 3
		3 1 4 2 6 5
		3 1 5 2 6 4
		3 1 5 4 6 2
		3 1 6 2 5 4
		3 1 6 4 5 2
		3 2 4
		3 2 5
														nr_of_		nr_of_
		less than	greater than	player				less_than	greater_than
 		1,2			4,5,6			3					2			3

	>												>							nr_of_less_than > 0
					2,4,5,6			1					0			4			if the smallest is taken, decrease nr_of_less_than and increase nr_of_greater_than.
		1			4,5,6			2					1			3			else, only decrease nr_of_less_than

	<												<							nr_of_greater_than > 0
					4,5,6			2		x			0			3	x		if the smallest is taken, only decrease nr_of_greater_than
		2			5,6				4					1			2			if not the smallest is taken, increase nr_of_less_than and descrease nr_of_greater_than.
		2,4			6				5					2			1
		2,4,5						6					3			0

	>												>							nr_of_less_than > 0
					5,6				2					0			2
					4,6				2					0			2			if the smallest is taken, decrease nr_of_less_than and increase nr_of_greater_than.
		2			6				4					1			1
					4,5				2					0			2			the smallest is taken
		2			5				4					1			1			the middle of three is taken
		2,4							5		x			2			0			the biggest is taken

	<																			nr_of_greater_than > 0
					6				5		x			0			1	x
		5							6					1			0			if not the smallest is taken, ...
					6				4		x			0			1	x
		4							6					1			0			if not the smallest is taken, ...
		2							6					1			0
					5				4		x			0			1	x
		4							5					1			0			if not the smallest is taken, ...
		2							5					1			0

	>																			nr_of_less_than > 0
									5					0			0
									4					0			0
									2					0			0
									4					0			0
									2					0			0
*/

