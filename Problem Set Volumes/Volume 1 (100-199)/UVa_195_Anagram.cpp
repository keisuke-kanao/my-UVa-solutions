
/*
	UVa 195 - Anagram

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_195_Anagram.cpp
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

bool compare_letter(char i, char j)
{
	char li = tolower(i), lj = tolower(j);
	if (li < lj)
		return true;
	else if (li > lj)
		return false;
	else
		return i < j;
}

int main()
{
	int n;
	cin >> n;
	while (n--) {
		string word;
		cin >> word;
		sort(word.begin(), word.end(), compare_letter);
		do
			cout << word << endl;
		while (next_permutation(word.begin(), word.end(), compare_letter));
	}
	return 0;
}

