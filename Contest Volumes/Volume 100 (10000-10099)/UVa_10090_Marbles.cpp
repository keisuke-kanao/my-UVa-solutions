
/*
	7.6.7 Marbles
	PC/UVa IDs: 110707/10090, Popularity: B, Success rate: low Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10090_Marbles.cpp
*/

/*
The linear Diophantine equation
	ax + by = c
has a solution if and only if d = gcd(a, b) divides c.
If d | c, then one solution may be found by determining u and v such that d = ua + vb and then setting 
	x0 = uc/d, y0 = vc/d.
All other solutions are given by
	x = x0 + (b/d)t = u(c/d) + (b/d)t, y = y0 - (a/d)t = v(c/d) - (a/d)t.
Since x and y should be non-negative,
	 u(c/d) + (b/d)t >= 0, v(c/d) - (a/d)t >= 0, and a > 0, b > 0, c > 0.
Then,
	-u(c/b) <= t <= v(c/a)
And since t must be an integer, 
	ceil(-u(c/b)) <= t <= floor(v(c/a)).
This range can be empty, which means no solutions.
Note that if x and y are positive integers, then floor(x/y) = x/y, and ceil(x/y) = (x+y-1)/y.

The cost function
	c = c1x + c2y
can be represented using the above equations,
	c = c1u(c/d) + c2v(c/d) + (c1(b/d) - c2(a/d))t = (some const) + (another const)t.
Since it is a linear function, its minimum and maximums can occur only at the boundary of feasible region.
Check the two boundary points t = ceil(-u(c/b)) and floor(v(c/a)), then choose whichever one is cheaper.
*/

#include <iostream>
#include <cmath>
using namespace std;

int gcd(int a, int b, int& x, int& y) // find the gcd(a, b) and x, y such that a * x + b * y = gcd(a, b)
{
	if (b > a)
		return gcd(b, a, y, x);
	if (b == 0) {
		x = 1; y = 0;
		return a;
	}
	int x1, y1;
	int d = gcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - (a / b) * y1;
	return d;
}

bool store_marbles(int marbles, const pair<int, int>& type_1, const pair<int, int>& type_2,
	pair<long long, long long>& counts)
{
	int u, v;
	int d = gcd(type_1.second, type_2.second, u, v);
	if (marbles % d)
		return false;
	long long t_min = static_cast<long long>(ceil(static_cast<double>(-u) * marbles / type_2.second));
	long long t_max = static_cast<long long>(floor(static_cast<double>(v) * marbles / type_1.second));
	if (t_min > t_max)
		return false;
	// If the slope of the cost function is positive, the cost function has the minumum value at t_min,
	// else, it does at t_max.
	long long slope = static_cast<long long>(type_1.first) * (type_2.second / d) -
		static_cast<long long>(type_2.first) * (type_1.second / d);
	long long t = (slope > 0) ? t_min : t_max;
	counts.first = static_cast<long long>(u) * (marbles / d) + static_cast<long long>(type_2.second / d) * t;
	counts.second = static_cast<long long>(v) * (marbles/ d) - static_cast<long long>(type_1.second / d) * t;
	return true;
}

int main(int /* argc */, char** /* argv */)
{
	while (true) {
		int marbles;
		cin >> marbles;
		if (!marbles)
			break;
		pair<int, int> type_1, type_2; // the first field is cost, the second field is capacity
		cin >> type_1.first >> type_1.second >> type_2.first >> type_2.second;
		pair<long long, long long> counts;
		if (store_marbles(marbles, type_1, type_2, counts))
			cout << counts.first << ' ' << counts.second << endl;
		else
			cout << "failed\n";
	}
	return 0;
}

