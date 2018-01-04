
/*
	UVa 466 - Mirror, Mirror

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_466_Mirror_Mirror.cpp
*/

#include <iostream>
using namespace std;

const int n_max = 10;

bool is_same_pattern(int n, const char transformed[n_max][n_max], char pattern[n_max][n_max])
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (transformed[i][j] != pattern[i][j])
				return false;
	return true;
}

bool ninety_degree_rotation(int n, const char original[n_max][n_max], const char transformed[n_max][n_max],
	char pattern[n_max][n_max])
{
	for (int j = 0; j < n; j++)
		for (int i = n - 1; i >= 0; i--)
			pattern[j][n - 1 - i] = original[i][j];
	return is_same_pattern(n, transformed, pattern);
}

bool one_hundred_and_eighty_degree_rotation(int n, const char original[n_max][n_max], const char transformed[n_max][n_max],
	char pattern[n_max][n_max])
{
	for (int i = n - 1; i >= 0; i--)
		for (int j = n - 1; j >= 0; j--)
			pattern[n - 1 - i][n - 1 - j] = original[i][j];
	return is_same_pattern(n, transformed, pattern);
}

bool two_hundreds_and_seventy_degree_rotation(int n, const char original[n_max][n_max], const char transformed[n_max][n_max],
	char pattern[n_max][n_max])
{
	for (int j = n - 1; j >= 0; j--)
		for (int i = 0; i < n; i++)
			pattern[n - 1 - j][i] = original[i][j];
	return is_same_pattern(n, transformed, pattern);
}

bool vertical_reflection(int n, const char original[n_max][n_max], const char transformed[n_max][n_max],
	char pattern[n_max][n_max])
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			pattern[n - i - 1][j] = original[i][j];
	return is_same_pattern(n, transformed, pattern);
}

int main()
{
	char original[n_max][n_max], transformed[n_max][n_max], pattern[n_max][n_max], pattern_ex[n_max][n_max];
	int n;
	for (int pattern_nr = 1; cin >> n; pattern_nr++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				cin >> original[i][j];
			for (int j = 0; j < n; j++)
				cin >> transformed[i][j];
		}
		cout << "Pattern " << pattern_nr << " was ";
		if (is_same_pattern(n, original, transformed))
			cout << "preserved.\n";
		else if (ninety_degree_rotation(n, original, transformed, pattern))
			cout << "rotated 90 degrees.\n";
		else if (one_hundred_and_eighty_degree_rotation(n, original, transformed, pattern))
			cout << "rotated 180 degrees.\n";
		else if (two_hundreds_and_seventy_degree_rotation(n, original, transformed, pattern))
			cout << "rotated 270 degrees.\n";
		else if (vertical_reflection(n, original, transformed, pattern))
			cout << "reflected vertically.\n";
		else if (ninety_degree_rotation(n, pattern, transformed, pattern_ex))
			cout << "reflected vertically and rotated 90 degrees.\n";
		else if (one_hundred_and_eighty_degree_rotation(n, pattern, transformed, pattern_ex))
			cout << "reflected vertically and rotated 180 degrees.\n";
		else if (two_hundreds_and_seventy_degree_rotation(n, pattern, transformed, pattern_ex))
			cout << "reflected vertically and rotated 270 degrees.\n";
		else
			cout << "improperly transformed.\n";
	}
	return 0;
}

