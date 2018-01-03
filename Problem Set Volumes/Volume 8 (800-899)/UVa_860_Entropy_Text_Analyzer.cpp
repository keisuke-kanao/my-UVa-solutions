
/*
	UVa 860 - Entropy Text Analyzer

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_860_Entropy_Text_Analyzer.cpp
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>
#include <cmath>
using namespace std;

bool is_space(char c)
{
	return c == ' ' || c == '\t' || c == '\n';
}

bool is_punctuation(char c)
{
	return c == ',' || c == '.' || c == ':' || c == ';' || c == '!' || c == '?' || c == '"' || c == '(' || c == ')';
}

int main()
{
	while (true) {
		string line;
		getline(cin, line);
		if (line == "****END_OF_INPUT****")
			break;
		int nr_words = 0;
		map<string, int> words;
		while (line != "****END_OF_TEXT****") {
			transform(line.begin(), line.end(), line.begin(), (int(*)(int))tolower);
			for (const char* p =  line.c_str(); *p; ) {
				while (*p && (is_space(*p) || is_punctuation(*p)))
					p++;
				if (*p) {
					const char* q = p;
					while (*p && !is_space(*p) && !is_punctuation(*p))
						p++;
					pair<map<string, int>::iterator, bool> result = words.insert(make_pair(string(q, p - q), 0));
					result.first->second++;
					nr_words++;
				}
			}
			getline(cin, line);
		}
		double Emax = log10(static_cast<double>(nr_words)), Et = 0.0;
		for (map<string, int>::const_iterator wi = words.begin(), we = words.end(); wi != we; ++wi) {
			double nr = static_cast<double>(wi->second);
			Et += nr * (Emax - log10(nr));
		}
		Et /= nr_words;
		cout << nr_words << ' ' << fixed << setprecision(1) << Et << ' ' <<
			setprecision(0) << (Et * 100.0) / Emax  << endl;
	}
	return 0;
}

/*
Sample Input1

Midnight, not a sound from the pavement
Has the moon lost her memory?
She is smiling alone
In the lamplight, the withered leaves collect at my feet
And the wind begins to moan
****END_OF_TEXT****
Memory, all alone in the moonlight
I can dream of the old days
Life was beautiful then
I remember the time I knew what happiness was
Let the memory live again
****END_OF_TEXT****
****END_OF_INPUT****

Sample Output

33 1.4 93
31 1.3 89
*/

