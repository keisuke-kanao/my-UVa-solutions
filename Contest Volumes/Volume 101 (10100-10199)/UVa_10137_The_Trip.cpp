
/*
	1.6.3 The Trip
	PC/UVa IDs: 110103/10137, Popularity: B, Success rate: average Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10137_The_Trip.cpp
*/

#include <iostream>
#include <iomanip>
using namespace std;

int equalize_costs(int n, int* expenses)
{
	int average = n / 2;
	for (int i = 0; i < n; i++)
		average += expenses[i];
	average /= n;
	int plus = 0, minus = 0;
	for (int i = 0; i < n; i++)
		if (expenses[i] > average)
			plus += expenses[i] - average;
		else
			minus += average - expenses[i];
	return (minus < plus) ? minus : plus;
}

int main(int /* argc */, char** /* argv */)
{
	const int n_max = 1000; // max. number of students
	int expenses[n_max];
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		for (int i = 0; i < n; i++) {
			int dollars, cents;
			char dc; // decimal point
			cin >> dollars >> dc >> cents;
			expenses[i] = dollars * 100 + cents;
		}
		int exchanges = equalize_costs(n, expenses);
		cout << '$' << exchanges / 100 << '.' << setfill('0') << setw(2) << exchanges % 100 << endl;
	}
	return 0;
}

