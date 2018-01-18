
/*
	6.6.7 Self-describing Sequence
	PC/UVa IDs: 110607/10049, Popularity: C, Success rate: high Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10049_Self-describing_Sequence.cpp
*/

/*
Golomb sequence From Wikipedia, the free encyclopedia

In mathematics, the Golomb sequence, named after Solomon W. Golomb (but also called Silverman's sequence), 
is a non-decreasing integer sequence where a(n) is the number of times that n occurs in the sequence, 
starting with a(1) = 1, and with the property that for n > 1 each a(n) is the smallest integer which 
makes it possible to satisfy the condition. For example, a(1) = 1 says that 1 only occurs once in the 
sequence, so a(2) cannot be 1 too, but it can be, and therefore must be, 2. The first few values are:

	n		 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
	----------------------------------------------------------------------------------------------------
	a(n)	 1  2  2  3  3  4  4  4  5  5  5  6  6  6  6  7  7  7  7  8  8  8  8  9  9  9  9  9 10 10

	n		31 32 33 34 35 36 37 38 39 40 41 42 43 44 45
	----------------------------------------------------
	a(n)	10 10 10 11 11 11 11 11 12 12 12 12 12 12

	Colin Mallows has given an explicit recurrence relation a(1) = 1; a(n + 1) = 1 + a(n + 1 - a(a(n))).
*/

#include <iostream>
#include <set>
#include <utility>
#include <cassert>
using namespace std;

/*
	To speed up the calculation, generate a sorted list where the values are a(n) and the first numbers in 
	a sequence of a(n) are the keys:

	first number
		in a sequence of a(n)	 1  2  4  6  9 12 16 20 24 29 34 39
	----------------------------------------------------------------
	a(n)						 1  2  3  4  5  6  7  8  9 10 11 12
*/

struct golomb_sequence_comparator {
	bool operator() (const pair<int, int>& lhs, const pair<int, int>& rhs) const
		{return lhs.first < rhs.first;}
};

set< pair<int, int>, golomb_sequence_comparator > golomb_sequences;

int find_golomb_sequence(int n)
{
	set< pair<int, int>, golomb_sequence_comparator >::iterator i = golomb_sequences.lower_bound(pair<int, int>(n, 0));
	assert(i != golomb_sequences.end());
	if (i->first != n)
		i--;
	return i->second;
}

void generate_golomb_sequences(int max)
{
	int n = 1, s = 1;
	golomb_sequences.insert(pair<int, int>(n, s++));
	while (n < max) {
		n += find_golomb_sequence(find_golomb_sequence(n));
//		cout << "a(" << n << ") = " << s << endl;
		golomb_sequences.insert(pair<int, int>(n, s++));
	}
#ifdef DEBUG
	cout << "max.sequence = " << golomb_sequences.size() << endl;
#endif
}

int main(int /* argc */, char** /* argv */)
{
	generate_golomb_sequences(2000000000);
	int n;
	while (cin >> n) {
		if (!n)
			break;
		cout << find_golomb_sequence(n) << endl;
	}
	return 0;
}

