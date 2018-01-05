
/*
	UVa 10370 - Above Average

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10370_Above_Average.cpp
*/

#include <cstdio>
using namespace std;
const int n_max = 1000;
double grades[n_max];

int main()
{
	int c;
	scanf("%d", &c);
	while (c--) {
		int n;
		scanf("%d", &n);
		double sum = 0.0;
		for (int i = 0; i < n; i++) {
			scanf("%lf", &grades[i]);
			sum += grades[i];
		}
		int above_average = 0;
		for (int i = 0; i < n; i++)
			if (grades[i] * static_cast<double>(n) > sum) // grades[i] > sum / n
				above_average++;
		printf("%.3lf%%\n", (static_cast<double>(above_average) * 100.0) / static_cast<double>(n));
	}
	return 0;
}

