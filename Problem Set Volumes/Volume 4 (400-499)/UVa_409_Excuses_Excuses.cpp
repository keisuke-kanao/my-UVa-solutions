
/*
	UVa 409 - Excuses, Excuses!

	from 1996 ACM South Central Region Programming Contest Problem #4
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_SouthCen/1996/index.html)

	The ACM ICPC Problem Set Archive
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive.html)

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_409_Excuses_Excuses.cpp
*/

/*
For each keyword, try to find the keyword is in the excuse in multiple times.
	Keyword matching is case-insensitive.
	If found, see if it is delimited by the beginning or end of the excuse or any non-alphabetic character or a space.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
using namespace std;

#ifdef ONLINE_JUDGE
#define _strnicmp strncasecmp
#endif

bool compare_number_of_keywords(const pair<string, int>& i, const pair<string, int>& j)
{
	return i.second > j.second;
}

inline bool is_delimiter(char c)
{
	// [#@".,!?&0123456789 ]
	return c >= '0' && c <= '9' || c >= ' ' && c <= '#' || c == '@' || c == '.' ||
		c == ',' || c == '?' || c == '&';
}

int count_keyword_incidences(const char* excuse, const char* keyword)
{
	int count = 0, length = strlen(keyword);
	for (const char *p = excuse, *q = p + strlen(excuse), *r = q - length + 1;
		p < r; p++) { // try to find the keyword is in the excuse in multiple times
		if (!_strnicmp(p, keyword, length)) {
			// 	If a keyword is found, see if it is delimited by the beginning or end of the excuse or 
			// any non-alphabetic character or a space.
			if ((p == excuse || is_delimiter(*(p - 1))) &&
				(p + length == q || is_delimiter(*(p + length)))) {
				count++;
				p += length;
			}
		}
	}
	return count;
}

int main()
{
	for (int nr_set = 1; ; nr_set++) {
		string line;
		if (!getline(cin, line))
			break; // EOF
		istringstream iss(line);
		int nr_keywords, nr_excuses;
		iss >> nr_keywords >> nr_excuses;
		vector<string> keywords(nr_keywords);
		for (int i = 0; i < nr_keywords; i++)
			getline(cin, keywords[i]);
		vector< pair<string, int> > excuses(nr_excuses, pair<string, int>(string(), 0));
			// excuses[i].fisrt is an excuse string, excuses[i].second is the number of keywords in the excuse string
		for (int i = 0; i < nr_excuses; i++) {
			getline(cin, line);
			excuses[i].first = line;
		}
		for (int i = 0; i < nr_excuses; i++)
			for (int j = 0; j < nr_keywords; j++)
				excuses[i].second += count_keyword_incidences(excuses[i].first.c_str(), keywords[j].c_str());
		// stable sort the vector of excuses in descending order of their number of keywords
		stable_sort(excuses.begin(), excuses.end(), compare_number_of_keywords);
#ifdef DEBUG
		for (int i = 0; i < nr_excuses; i++)
			cerr << excuses[i].second << ": " << excuses[i].first << endl;
#endif
		cout << "Excuse Set #" << nr_set << endl;
		int i = 0, j = excuses[0].second;
		do
			cout << excuses[i].first << endl;
		while (++i < nr_excuses && excuses[i].second == j);
		cout << endl;
	}
	return 0;
}

