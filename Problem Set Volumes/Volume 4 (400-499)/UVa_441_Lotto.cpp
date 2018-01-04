
/*
	UVa 441 - Lotto

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_441_Lotto.cpp

	from University of Ulm Local Contest 1996 Problem F
		(http://www.informatik.uni-ulm.de/acm/Locals/1996/)
*/

#include <iostream>
using namespace std;

const int max_nr_to_choose = 6, k_max = 12;
int integers[k_max];
bool chosen_integers[k_max]; // chosen_integers[i] is true if integers[i] is chosen for a game

void print_game(int i, int k, int nr_to_choose)
{
	if (!nr_to_choose) {
		bool printed = false;
		for (int j = 0; j < k; j++)
			if (chosen_integers[j]) {
				if (printed)
					cout << ' ';
				else
					printed = true;
				cout << integers[j];
			}
		cout << endl;
	}
	else {
		for (int j = i; j < k - nr_to_choose + 1; j++) {
			chosen_integers[j] = true;
			print_game(j + 1, k, nr_to_choose - 1);
			chosen_integers[j] = false;
		}
	}
}

int main()
{
	bool printed = false;
	while (true) {
		int k;
		cin >> k;
		if (!k)
			break;
		if (printed)
			cout << endl;
		for (int i = 0; i < k; i++)
			cin >> integers[i];
		for (int i = 0; i < k - max_nr_to_choose + 1; i++) {
			chosen_integers[i] = true;
			print_game(i + 1, k, max_nr_to_choose - 1);
			chosen_integers[i] = false;
		}
		printed = true;
	}
	return 0;
}

