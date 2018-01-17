
/*
	3.8.3 Common Permutation
	PC/UVa IDs: 110303/10252, Popularity: A, Success rate: average Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10252_Common_Permutation.cp
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main(int /* argc */, char** /* argv */)
{
	string a, b;
	while (getline(cin, a) && getline(cin, b)) { // read two consecutive lines
		// sort the characters in each string
		sort(a.begin(), a.end());
		sort(b.begin(), b.end());
		const int number_of_lowercase_characters = 'z' - 'a' + 1;
		int counts[number_of_lowercase_characters]; // i-th slot is the number of how many times ('a' + i-th) appears in string a
		for (int i = 0; i < number_of_lowercase_characters; i++)
			counts[i] = 0;
		for (int i = 0; i < a.length(); i++)
			counts[a[i] - 'a']++;
		string x;
		for (int i = 0; i < b.length(); i++)
			if (counts[b[i] - 'a']) {
				counts[b[i] - 'a']--;
				x += b[i];
			}
		cout << x << endl;
	}
	return 0;
}

