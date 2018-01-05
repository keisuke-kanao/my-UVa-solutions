
/*
	UVa 11221 - Magic square palindromes.

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11221_Magic_square_palindromes.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

bool is_palindrome(const char* s, int length)
{
	for (int i = 0, j = length - 1; i < j; i++, j--)
		if (s[i] != s[j])
			return false;
	return true;
}

int main()
{
	int t;
	cin >> t;
	string line;
	getline(cin, line); // skip '\n'
	for (int case_nr = 1; case_nr <= t; case_nr++) {
		getline(cin, line);
		int length = line.length();
		char* msp = new char[length + 1];
		int msp_length = 0;
		for (int i = 0; i < length; i++)
			if (!isspace(line[i]) && !ispunct(line[i]))
				msp[msp_length++] = line[i];
		msp[msp_length] = '\0';
#ifdef DEBUG
		cout << msp << endl;
#endif
		int msp_dimension = 0;
		if (is_palindrome(msp, msp_length)) {
			msp_dimension = static_cast<int>(sqrt(static_cast<double>(msp_length)));
			if (msp_dimension * msp_dimension == msp_length) {
				char* msp_original = new char[msp_length + 1];
				strcpy(msp_original, msp);
				vector< vector<char> > square(msp_dimension, vector<char>(msp_dimension));
				// generate a square in the moving-right order
				for (int i = 0; i < msp_dimension; i++)
					for (int j = 0; j < msp_dimension; j++)
						square[i][j] = msp[i * msp_dimension + j]; // move right
				// check in moving-down order
				for (int j = 0; j < msp_dimension; j++)
					for (int i = 0; i < msp_dimension; i++)
						msp[j * msp_dimension + i] = square[i][j];
				if (!strcmp(msp, msp_original)) {
					// check in the moving-left order
					for (int i = 0; i < msp_dimension; i++)
						for (int j = 0; j < msp_dimension; j++)
							msp[i * msp_dimension + j] = square[msp_dimension - i - 1][msp_dimension - j - 1];
					if (!strcmp(msp, msp_original)) {
						// check in the moving-up order
						for (int j = 0; j < msp_dimension; j++)
							for (int i = 0; i < msp_dimension; i++)
							msp[j * msp_dimension + i] = square[msp_dimension - i - 1][msp_dimension - j - 1];
							if (strcmp(msp, msp_original))
								msp_dimension = 0;
					}
					else
						msp_dimension = 0;
				}
				else
					msp_dimension = 0;
				delete[] msp_original;
			}
			else
				msp_dimension = 0;
		}
		cout << "Case #" << case_nr << ":\n";
		if (msp_dimension)
			cout << msp_dimension << endl;
		else
			cout << "No magic :(\n";
		delete msp;
	}
	return 0;
}

