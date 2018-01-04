
/*
	UVa 296 - Safebreaker

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_296_Safebreaker.cpp
*/

#include <iostream>
#include <cstring>
using namespace std;

const int nr_digits = 4, nr_guesses_max = 10, number_max = 10000;

struct guess {
	char code_[nr_digits + 1];
	int nr_correct_, nr_misplaced_;
};

void get_code(int n, char* code)
{
	for (int i = nr_digits - 1; i >= 0; i--) {
		code[i] = n % 10 + '0';
		n /= 10;
	}
}

bool is_consistent(const char* code, const guess* g)
{
	int nr_correct = 0;
	unsigned char correct = 0; // bit i (0 <= i <= 4) is 1 if i-th character is correct
	for (int i = 0, bi = 1; i < nr_digits; i++, bi <<= 1)
		if (code[i] == g->code_[i]) {
			correct |= bi;
			nr_correct++;
		}
	if (nr_correct != g->nr_correct_)
		return false;
	int nr_misplaced = 0;
	unsigned char misplaced = 0; // bit i (0 <= i <= 4) is 1 if i-th character is misplaced
	for (int i = 0, bi = 1; i < nr_digits; i++, bi <<= 1)
		if (!(correct & bi)) {
			int j = i + 1;
			if (j == nr_digits)
				j = 0;
			while (j != i) {
				int bj = 1 << j;
				if (!(correct & bj) && !(misplaced & bj) && code[i] == g->code_[j]) {
					misplaced |= bj;
					nr_misplaced++;
					break;
				}
				if (++j == nr_digits)
					j = 0;
			}
		}
	return nr_misplaced == g->nr_misplaced_;
}

int main()
{
	int n;
	cin >> n;
	while (n--) {
		int g;
		cin >> g;
		guess guesses[nr_guesses_max];
		for (int i = 0; i < g; i++) {
			char separator;
			cin >> guesses[i].code_ >> guesses[i].nr_correct_ >> separator >> guesses[i].nr_misplaced_;
		}
		int nr_consistent = 0;
		char code[nr_digits + 1], secret_code[nr_digits + 1];
		code[nr_digits] = '\0';
		for (int i = 0; i < number_max; i++) {
			get_code(i, code);
			int j;
			for (j = 0; j < g; j++)
				if (!is_consistent(code, &guesses[j]))
					break;
			if (j == g) {
				if (!nr_consistent++)
					strcpy(secret_code, code);
			}
		}
		if (nr_consistent == 1)
			cout << secret_code << endl;
		else if (nr_consistent)
			cout << "indeterminate\n";
		else
			cout << "impossible\n";
	}
	return 0;
}

