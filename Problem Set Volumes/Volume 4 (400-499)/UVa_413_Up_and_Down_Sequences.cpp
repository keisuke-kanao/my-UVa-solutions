
/*
	UVa 413 - Up and Down Sequences

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_413_Up_and_Down_Sequences.cpp

	from 1995 ACM East Central Regionals
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_EastCen/1995/index.html)
*/

#include <cstdio>

int main()
{
	while (true) {
		const int n_max = 30;
		int values[n_max + 1];
		scanf("%d", &values[0]);
		if (!values[0])
			break;
		int n = 1;
		while (true) {
			scanf("%d", &values[n]);
			if (!values[n])
				break;
			n++;
		}
		int up_down = 0; // 1 for up sequence, -1 for down sequence
		int nr_ups = 0, nr_downs = 0, up_length_sum = 0, down_length_sum = 0, length = 0;
		for (int i = 1; i < n; i++) {
			if (values[i] > values[i - 1] && up_down <= 0) { // start of an up sequence
				if (up_down < 0)
					down_length_sum += length;
				else
					up_length_sum += length;
				up_down = 1; nr_ups++; length = 0;
			}
			else if (values[i] < values[i - 1] && up_down >= 0) { // start of a down sequence
				if (up_down > 0)
					up_length_sum += length;
				else
					down_length_sum += length;
				up_down = -1; nr_downs++; length = 0;
			}
			length++;
		}
		if (up_down > 0)
			up_length_sum += length;
		else if (up_down < 0)
			down_length_sum += length;
		double average_up_length = (nr_ups) ? static_cast<double>(up_length_sum) / static_cast<double>(nr_ups) : 0.0,
			average_down_length = (nr_downs) ? static_cast<double>(down_length_sum) / static_cast<double>(nr_downs) : 0.0;
		printf("Nr values = %d:  %.6lf %.6lf\n", n, average_up_length, average_down_length);
	}
	return 0;
}

