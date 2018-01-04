
/*
	UVa 11579 - Triangle Trouble

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11579_Triangle_Trouble.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

const int N_max = 10000;
double sides[N_max];

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		int N;
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%lf", &sides[i]);
		sort(sides, sides + N);
		double largest = 0.0;
		for (int i = 0; i < N - 2; i++) {
			double a = sides[i], b = sides[i + 1], c = sides[i + 2];
			if (a + b < c || b + c < a || c + a < b)
				continue;
			double s = (a + b + c) / 2.0,
				sa = s * (s - a) * (s - b) * (s - c); // Heron's formula
			largest = max(largest, sa);
		}
		printf("%.2lf\n", ((largest > 0.0) ? sqrt(largest) : largest));
	}
	return 0;
}

/*

Sample Input

2
4 3.0 4.0 5.0 100.0
3 1.0 2.0 4.0

Sample Output

6.00
0.00

*/

