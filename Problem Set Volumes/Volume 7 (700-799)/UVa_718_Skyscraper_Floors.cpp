
/*
	UVa 718 - Skyscraper Floors

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_718_Skyscraper_Floors.cpp
*/

/*
To see if an elevator reaches a floor is really easy. 
If the elevator is of the form ax + c then we must check if f >= c and (f - c) % a == 0.

Now we must check which elevators are connected. For that we want a pair of integers (x, y) such that:
  1. ax + c1 = by + c2 <=> ax - by = c2 - c1
  2. c1 <= ax + c1 <= nf
  3. c2 <= by + c2 <= nf
For this you must know how to solve linear diophantine equations. 
1003linearDiophantine.pdf give the general solution. 
You just have to replace it on the conditions 2. and 3. and solve for t. 
Then you will get l1 <= t <= r1 and l2 <= t <= r2 for some integers l1, r1, l2 and r2.
*/

#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

long long gcd_ex(long long a, long long b, long long& x, long long& y) // extended Euclidean Algorithm
{
	if (b == 0) {
		x = 1, y = 0;
		return a;
	}
	long long x1, y1;
	long long d = gcd_ex(b, a % b, x1, y1);
	x = y1, y = x1 - (a / b) * y1;
	return d;
}

bool linear_diophantine_equation(int a, int b, int c, long long& d, long long& x0, long long& y0)
{
	long long u, v;
	d = gcd_ex(a, b, u, v);
	if (c % d)
		return false;
	x0 = u * (c / d), y0 = v * (c / d);
	return true;
}

bool reachable(int Xi, int Xj, int Yi, int Yj, int F)
{
	long long d, x0, y0;
	if (!linear_diophantine_equation(Xi, -Xj, Yj - Yi, d, x0, y0))
		return false;
	int xi = static_cast<int>(Xi / d), xj = static_cast<int>(-Xj / d);
	double d_min = static_cast<double>(-x0) / xj, d_max = (static_cast<double>(F - 1 - Yi) / Xi - x0) / xj;
	if (xj < 0)
		swap(d_min, d_max);
	int ti_min = static_cast<int>(ceil(d_min)), ti_max = static_cast<int>(floor(d_max));
	d_min = (y0 - static_cast<double>(F - 1 - Yj) / Xj) / xi, d_max = static_cast<double>(y0) / xi;
	if (xi < 0)
		swap(d_min, d_max);
	int tj_min = static_cast<int>(ceil(d_min)), tj_max = static_cast<int>(floor(d_max));
	return (ti_min > tj_max || ti_max < tj_min) ? false : true;
}

const int E_max = 100;

int Xs[E_max], Ys[E_max];
bool A_reachables[E_max], B_reachables[E_max], reachables[E_max][E_max];

int main()
{
	int N;
	scanf("%d", &N);
	while (N--) {
		int F, E, A, B;
		scanf("%d %d %d %d", &F, &E, &A, &B);
		for (int i = 0; i < E; i++)
			scanf("%d %d", &Xs[i], &Ys[i]);
		for (int i = 0; i < E; i++) {
			A_reachables[i] = A >= Ys[i] && !((A - Ys[i]) % Xs[i]);
			B_reachables[i] = B >= Ys[i] && !((B - Ys[i]) % Xs[i]);
		}
		for (int i = 0; i < E - 1; i++)
			for (int j = i + 1; j < E; j++)
				reachables[i][j] = reachables[j][i] = reachable(Xs[i], Xs[j], Ys[i], Ys[j], F);
#ifdef DEBUG
		for (int i = 0; i < E - 1; i++)
			for (int j = i + 1; j < E; j++)
				if (reachables[i][j])
					printf("[%d][%d] ", i, j);
		putchar('\n');
#endif
		for (int k = 0; k < E; k++)
			for (int i = 0; i < E; i++)
				for (int j = 0; j < E; j++)
					reachables[i][j] |= reachables[i][k] && reachables[k][j];
		bool possible = false;
		for (int i = 0; i < E && !possible; i++)
			if (A_reachables[i])
				for (int j = 0; j < E && !possible; j++)
					if (B_reachables[j] && reachables[i][j])
						possible = true;
		puts((possible) ? "It is possible to move the furniture." :
			"The furniture cannot be moved.");
	}
	return 0;
}

