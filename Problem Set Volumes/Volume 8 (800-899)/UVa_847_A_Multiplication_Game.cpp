
/*
	5.9.5 A Multiplication Game
	PC/UVa IDs: 110505/847, Popularity: A, Success rate: high Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_847_A_Multiplication_Game.cpp
*/

/*
This is an application of minmax algorithm in which on Stan's turn, we get the maximum number by 
multiplying it by nine and on Ollie's turn, we get the minimum number by multiplying it by two.

For more information about minmax algorithm, see the following sites:
	"CS312 Recitation 21 Minimax search and Alpha-Beta Pruning"
		http://www.cs.cornell.edu/Courses/cs312/2002sp/lectures/rec21.htm
	"Game Trees"
		http://www.ocf.berkeley.edu/~yosenl/extras/alphabeta/alphabeta.html

Sample inputs and thier corresponding outputs are:
	2			Stan wins.
	10			Ollie wins.
	18			Ollie wins.
	19			Stan wins.
	162			Stan wins.
	163			Ollie wins.
	1459		Stan wins.
	13123		Stan wins.
	118099		Stan wins.
	1062883		Ollie wins.
	(4294967295	Stan wins.)
*/

#include <iostream>
#include <cmath>
using namespace std;

#ifdef DEBUG
bool multiplication_game_recursive(unsigned int n)
{
	if (n == 1)
		return false;
	unsigned int m = n / 9;
	if (n % 9)
		m++;
	if ( m == 1)
		return true;
	unsigned int l = m / 2;
	if (m % 2)
		l++;
	return multiplication_game_recursive(l);
}
#endif

int multiplication_game(long long x, long long n, int count)
{
	x *= 9; // on Stan's turn, we get the maximum number by multiplying it by nine
	if (x >= n)
		return count;
	else {
		x *= 2; // on Ollie's turn, we get the minimum number by multiplying it by two
		if (x >= n)
			return count + 1;
		else
			return multiplication_game(x , n, count + 2);
	}
}

int main(int /* argc */, char ** /* argv */)
{
	unsigned int n;
	while (cin >> n) {
#ifdef DEBUG
		cout << ((multiplication_game_recursive(n)) ? "Stan" : "Ollie") << " wins.\n";
#endif
		cout << ((multiplication_game(1, n, 1) % 2) ? "Stan" : "Ollie") << " wins.\n";
	}
	return 0;
}

