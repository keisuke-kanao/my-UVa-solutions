
/*
	UVa 11181 - Probability|Given

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11181_Probability_Given.cpp
*/

/*
	For example - first test case... 
	3 people, 2 of this person buy something. 
	There are only C(3,2) = 3 possibilities: 
	  a) 1 & 2 buy something, 3 not, probability of this is 0,1 * 0,2 * 0,7 = 0,014 
	  b) 1 & 3 buy something, 2 not, probability of this is 0,1 * 0,8 * 0,3 = 0,024 
	  c) 2 & 3 buy something, 1 not, probability of this is 0,9 * 0,2 * 0,3 = 0,054 

	The total probability of this three events is 0,014 + 0,024 + 0,054 = 0,092. 

	Let's determine probability, that person 1 buy something. 
	This is true in cases a) and b). Also (0,014 + 0,024) /0,092 = 0,413043478 
	For person 2 -> in cases a) and c) person 2 buy something. Also (0,014+0,054)/0,092 = 0,739130434 
	For person 3 -> in cases b) and c) person 3 buy something. Also (0,024+0,054)/0,092 = 0,847826087 
*/

/*
	Let p[i] is the buying probability of the i-th friend, and
		q(i, j) is the probability that j of the first i friends (1, 2, ...i) buy something, then:
		q(i, j) = p[i] * q(i - 1, j - 1) + (1 - p[i]) * q(i - 1, j).
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int n_max = 20;
double p[n_max + 1];
	// p[i] is the buying probability of the i-th friend 
double q[n_max + 1][n_max + 1];
	// q[i][j] is the probability that j of the first i friends (1, 2, ...i) buy something

int main()
{
	for (int c = 1; ; c++) {
		int n, r;
		cin >> n >> r;
		if (!n && !r)
			break;
		for (int i = 1; i <= n; i++)
			cin >> p[i];
		cout << "Case " << c << ":\n";
		memset(q, 0, sizeof(q));
		q[0][0] = 1.0;
		for (int i = 1; i <= n; i++) {
			q[i][0] = (1.0 - p[i]) * q[i - 1][0];
			for (int j = 1; j <= min(i, r); j++)
				q[i][j] = p[i] * q[i - 1][j - 1] + (1.0 - p[i]) * q[i - 1][j];
		}
		double t = q[n][r];
		for (int k = 1; k <= n; k++) {
			memset(q, 0, sizeof(q));
			q[0][0] = 1.0;
			for (int i = 1; i <= n; i++) {
				if (i == k) { // k-th friend buys something
					q[i][0] = 0.0;
					for (int j = 1; j <= min(i, r); j++)
						q[i][j] = p[i] * q[i - 1][j - 1];
				}
				else {
					q[i][0] = (1.0 - p[i]) * q[i - 1][0];
					for (int j = 1; j <= min(i, r); j++)
						q[i][j] = p[i] * q[i - 1][j - 1] + (1.0 - p[i]) * q[i - 1][j];
				}
			}
			printf("%.6lf\n", q[n][r] / t);
		}
	}
	return 0;
}

