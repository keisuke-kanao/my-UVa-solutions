
/*
	UVa 489 - Hangman Judge

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_489_Hangman_Judge.cpp
*/

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main()
{
	const int nr_strokes_max = 7;
	while (true) {
		int r;
		cin >> r;
		if (r == -1)
			break;
		char turned_overs['z' - 'a' + 1];
		memset(turned_overs, -1, sizeof(turned_overs));
		string solution;
		cin >> solution;
		int nr_letters = 0;
		for (int i = 0, e = solution.length(); i < e; i++)
			if (turned_overs[solution[i] - 'a'] == -1) {
				++nr_letters;
				turned_overs[solution[i] - 'a'] = 1;
			}
		string guess;
		cin >> guess;
		int nr_strokes = 0;
		for (int i = 0, e = guess.length(); i < e; i++) {
			if (turned_overs[guess[i] - 'a'] == 1) {
				if (!--nr_letters)
					break;
				turned_overs[guess[i] - 'a'] = 2;
			}
			else if (turned_overs[guess[i] - 'a'] == -1) {
				if (++nr_strokes == nr_strokes_max)
					break;
				turned_overs[guess[i] - 'a'] = -2;
			}
		}
		cout << "Round " << r << endl;
		if (!nr_letters)
			cout << "You win.\n";
		else if (nr_strokes == nr_strokes_max)
			cout << "You lose.\n";
		else
			cout << "You chickened out.\n";
	}
	return 0;
}

