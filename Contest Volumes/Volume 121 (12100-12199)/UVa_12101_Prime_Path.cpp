
/*
	UVa 12101 - Prime Path

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12101_Prime_Path.cpp
*/

#include <queue>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const int n_min = 1000, n_max = 9999, nr_digits = '9' - '0' + 1;

bool not_primes[n_max + 1]; // not_primes[i] is true if i is not a prime
bool visited[n_max + 1];

void sieve_of_eratosthenes()
{
	not_primes[0] = not_primes[1] = true;
	for (int i = 2, e = static_cast<int>(sqrt(static_cast<double>(n_max))); i <= e; i++)
		if (!not_primes[i]) {
			for (int j = i * i; j <= n_max; j += i)
				not_primes[j] = true;
		}
}

struct path {
	int p_; // prime
	int s_; // steps

	path(int p, int s) : p_(p), s_(s) {}
};

void push_prime(queue<path>& q, int s, int d0, int d1, int d2, int d3)
{
	int p = d0 * 1000 + d1 * 100 + d2 * 10 + d3;
	if (!not_primes[p] && !visited[p]) {
		visited[p] = true;
		q.push(path(p, s));
	}
}

int bfs(int start, int end)
{
	queue<path> q;
	memset(visited, 0, sizeof(visited));
	visited[start] = true;
	q.push(path(start, 0));
	while (!q.empty()) {
		path p = q.front();
		q.pop();
		if (p.p_ == end)
			return p.s_;
		int d0 = p.p_ / 1000, d1 = p.p_ % 1000 / 100, d2 = p.p_ % 100 / 10, d3 = p.p_ % 10, s = p.s_ + 1;
		for (int d = 1; d < nr_digits; d++)
			push_prime(q, s, d, d1, d2, d3);
		for (int d = 0; d < nr_digits; d++)
			push_prime(q, s, d0, d, d2, d3);
		for (int d = 0; d < nr_digits; d++)
			push_prime(q, s, d0, d1, d, d3);
		for (int d = 1; d < nr_digits; d += 2)
			push_prime(q, s, d0, d1, d2, d);
	}
	return -1;
}

int main()
{
	sieve_of_eratosthenes();
	int t;
	scanf("%d", &t);
	while (t--) {
		int start, end;
		scanf("%d %d", &start, &end);
		int steps = bfs(start, end);
		if (steps != -1)
			printf("%d\n", steps);
		else
			puts("Impossible");
	}
	return 0;
}

