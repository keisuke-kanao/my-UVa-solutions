
/*
	UVa 11003 - Boxes

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11003_Boxes.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 1000, weight_max = 3000, max_load_max = 3000;
const int min_weights_max = weight_max * n_max + 1;

struct box {
	int weight_;
	int max_load_;
} boxes[n_max + 1];

int min_weights[2][n_max + 1];
	// min_weights[i][j] is the minimum weights of j boxes out of (i % n) boxes, 1 <= i <= n, 1 <= j <= i

int stack_boxes(int n)
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j <= n; j++)
			min_weights[i][j] = (j) ? min_weights_max : 0;
	for (int i = 1; i <= n; i++) {
		int pi = (i - 1) % 2, ci = i % 2;
		for (int j = 1; j <= i; j++) {
			min_weights[ci][j] = min_weights[pi][j];
			if (min_weights[pi][j - 1] <= boxes[i].max_load_ &&
				min_weights[ci][j] > min_weights[pi][j - 1] + boxes[i].weight_)
				min_weights[ci][j] = min_weights[pi][j - 1] + boxes[i].weight_;
		}
#ifdef DEBUG
		for (int j = 1; j <= n; j++)
			printf("%d%c", min_weights[ci][j], ((j == n) ? '\n' : ' '));
#endif
	}
	int k = n;
	for ( ; min_weights[n % 2][k] == min_weights_max; k--)
		;
	return k;
}

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		for (int i = n; i >= 1; i--)
			scanf("%d %d", &boxes[i].weight_, &boxes[i].max_load_);
		printf("%d\n", stack_boxes(n));
	}
	return 0;
}

