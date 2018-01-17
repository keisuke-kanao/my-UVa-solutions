
/*
	3.8.4 Crypt Kicker II
	PC/UVa IDs: 110304/850, Popularity: A, Success rate: average Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc -DONLINE_JUDGE UVa_850_Crypt_Kicker_II.cpp
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

bool compare_with_reference_string(const string& s, const string& t)
{
	// compare the two strings such that the two strings are considered equal 
	// if the lengths are equal and the positions of spaces are equal
	if (s.length() != t.length())
		return false;
	for (int i = 0; i < s.length(); i++) {
		if (isalpha(s[i])) {
			if (!isalpha(t[i]))
				return false;
		}
		else { // the letter should be a space
			if (t[i] != ' ')
				return false;
		}
	}
	return true;
}

/*
	xnm ceuob lrtzv ita hegfd tsmr xnm ypwq ktj
	the quick brown fox jumps over the lazy dog

	decrypt_letters['a' - 'a'] = 'x'
	decrypt_letters['b' - 'a'] = 'k'
	decrypt_letters['c' - 'a'] = 'q'
	...
	decrypt_letters['y' - 'a'] = 'l'
	decrypt_letters['z' - 'a'] = 'w'
*/

bool decrypt_letters(const string& crypted_string, const string& decrypted_string, vector<char>& decrypted_letters)
{
	decrypted_letters.assign(decrypted_letters.size(), '\0');
	// generate a character table where i-th slot has decrypt letter for the i-th character starting from 'a'
	for (int i = 0; i < decrypted_string.length(); i++)
		if (isalpha(crypted_string[i])) {
			int j = crypted_string[i] - 'a';
			if (decrypted_letters[j] != '\0' && decrypted_letters[j] != decrypted_string[i])
				return false;
			decrypted_letters[j] = decrypted_string[i];
		}
	return find(decrypted_letters.begin(), decrypted_letters.end(), '\0') == decrypted_letters.end();
}

int main(int /* argc */, char** /* argv */)
{
	string line;
	istringstream iss;

	// read the number of cases
	if (!getline(cin, line))
		return 0;
	iss.str(line);
	int cases;
	iss >> cases;
	iss.clear();
	if (cases && !getline(cin, line)) // skip a blank line
		return 0;
	for (int c = 0; c < cases; c++) {
		vector<string> lines;
		while (getline(cin, line)) { // read lines
			if (line.empty())
				break;
			lines.push_back(line);
		}

		const string brown_fox = "the quick brown fox jumps over the lazy dog";
		int found = 0;
		string reference;
		vector<char> decrypted_letters('z' - 'a' + 1);
		for (vector<string>::const_iterator i = lines.begin(); i != lines.end(); i++)
			if (compare_with_reference_string(*i, brown_fox)) {
				if (!found && decrypt_letters(*i, brown_fox, decrypted_letters)) {
					reference = *i; found++;
#ifdef ONLINE_JUDGE
					break;
#else
				}
				else {
					if (*i == reference)
						continue;
					vector<char> another_decrypted_letters('z' - 'a' + 1);
					if (decrypt_letters(*i, brown_fox, another_decrypted_letters) &&
						!equal(decrypted_letters.begin(), decrypted_letters.end(), another_decrypted_letters.begin())) {
						found = -1; break;
					}
#endif
				}
			}

		if (found <= 0) // a reference string was not found or more than one reference strings were found
			cout << "No solution.\n";
		else {
			// decrypt the lines
			for (vector<string>::const_iterator i = lines.begin(); i != lines.end(); i++) {
				for (int j = 0; j < (*i).length(); j++)
					cout << ((isalpha((*i)[j])) ? decrypted_letters[(*i)[j] - 'a'] : (*i)[j]);
				cout << endl;
			}
		}
		if (c < cases - 1)
			cout << endl; // output of each two consecutive cases must be separated by a blank line
	}
	return 0;
}

