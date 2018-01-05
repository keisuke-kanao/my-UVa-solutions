
/*
	UVa 10650 - Determinate Prime

	To build using Visucal Studio 2012:
		cl -EHsc UVa_10650_Determinate_Prime.cpp
*/

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int n_max = 32000;
bool not_primes[n_max + 1]; // not_primes[i] is true if i is not a prime
int determinate_primes[n_max + 1], uni_distances[n_max + 1];
	// determinate_primes[i] is the number of determinate primes starting at i, uni_distances[i] is its uni-distance

void sieve_of_eratosthenes()
{
	for (int i = 2, e = static_cast<int>(sqrt(static_cast<double>(n_max))); i <= e; i++)
		if (!not_primes[i]) {
			for (int j = i * i; j <= n_max; j += i)
				not_primes[j] = true;
		}
}

int main()
{
	sieve_of_eratosthenes();
	for (int i = 5, ppi = 2, pi = 3, dpi = -1; i <= n_max; i++)
		if (!not_primes[i]) {
			if (i - pi == pi - ppi) {
				if (dpi == -1) {
					dpi = ppi;
					determinate_primes[dpi] = 3;
					uni_distances[dpi] = pi - ppi;
				}
				else {
					determinate_primes[dpi]++;
/*
	See the below comment from the UVA forum
		(http://online-judge.uva.es/board/viewtopic.php?f=28&t=8705&start=45).

					if (determinate_primes[dpi] > 3) {
						int dp = determinate_primes[dpi] - 1, ud = uni_distances[dpi];
						int j = dpi + ud;
						do {
							determinate_primes[j] = dp--;
							uni_distances[j] = ud;
							j += ud;
						} while (dp >= 3);
					}
*/
				}
			}
			else
				dpi = -1;
			ppi = pi; pi = i;
		}
	while (true) {
		int x, y;
		cin >> x >> y;
		if (!x && !y)
			break;
		if (x > y)
			swap(x, y);
		for (int i = x; i < y; ) {
			if (determinate_primes[i] >= 3 && i + uni_distances[i] * (determinate_primes[i] - 1) <= y) {
				bool printed = false;
				for (int dp = determinate_primes[i], ud = uni_distances[i]; ; i += ud) {
					if (printed)
						cout << ' ';
					else
						printed = true;
					cout << i;
					if (!--dp || i + ud > y)
						break;
				}
				cout << endl;
			}
			else
				i++;
		}
	}
	return 0;
}

/*
Finally I got ac for 10650 but it is clear the difficulty for getting ac from 412 AC for 10650. 
I put these hints for those who got WA. 

1. If x>y then swap them and compute the result for [x,y]. 
2. In the problem desciption there's an important note. I translate it as : 
Suppose we have this sequence of primes by 6 unit diffrence. 
251 257 263 269 
If we want to consider above sequence as an answer we should be sure that all sequence numbers are in the [x,y]. 
So for input 252 269 we should print nothing since 251 is not included. Maybe you consider this part of problem : 
If three or more consecutive primes ...

and think 257 263 269 are a sequence of 3 uni-distance primes; 
but since 251 are one the members of 6 diffrence sequence and it is not included so it is not a desired answer. 

Finally try this input : 

250 268 
252 270 
255 269 
250 269 
251 270 
251 269 
250 270 
0 0 

output : 
251 257 263 269 
251 257 263 269 
251 257 263 269 
251 257 263 269 

for 1st , 2nd and 3rd print nothing and 4 next one have answer. 
*/

