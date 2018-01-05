
/*
	UVa 10686 - SQF Problems

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10686_SQF_Problems.cpp

	Ugly.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <cctype>
using namespace std;

const int C_max = 20, W_max = 10;

struct category {
	string name_;
	int nr_keywords_, nr_appear_;
	bool keywords_[W_max];

	category() {}
} categories[C_max];

bool is_duplicated_keyword(int ci, const string& w, multimap< string, pair<int, int> >& keywords)
{
	pair < multimap<string, pair<int, int> >::iterator, multimap<string, pair<int, int> >::iterator > result = keywords.equal_range(w);
	for (multimap<string, pair<int, int> >::iterator i = result.first; i != result.second; ++i)
		if (i->second.first == ci)
			return true;
	return false;
}

char remove_nonalpha(char c)
{
	return (isalpha(c)) ? c : ' ';
}

int main()
{
	string line;
	istringstream iss;
	getline(cin, line);
	iss.str(line);
	int N;
	iss >> N;
	iss.clear();
	while (N--) {
		getline(cin, line);
		iss.str(line);
		int C;
		iss >> C;
		iss.clear();
		multimap< string, pair<int, int> > keywords;
			// key is a keyword, value is the index pair to categories[i].keywords_[j]
		for (int i = 0; i < C; i++) {
			category& c = categories[i];
			getline(cin, line);
			iss.str(line);
			iss >> c.name_ >> c.nr_keywords_ >> c.nr_appear_;
			iss.clear();
			for (int j = 0; j < c.nr_keywords_; ) {
				getline(cin, line);
				iss.str(line); // to remove blanks
				string w;
				iss >> w;
				iss.clear();
				if (is_duplicated_keyword(i, w, keywords))
					c.nr_keywords_--;
				else {
					keywords.insert(make_pair(w, make_pair(i, j)));
					c.keywords_[j] = false;
					j++;
				}
			}
		}
#ifdef DEBUG
		for (multimap<string, pair<int, int> >::const_iterator ki = keywords.begin(), ke = keywords.end(); ki != ke; ++ki)
			cout << ki->first << " (" << ki->second.first << ", " << ki->second.second << ")\n";
#endif
		while (getline(cin, line) && !line.empty()) {
			transform(line.begin(), line.end(), line.begin(), remove_nonalpha); // replace non-alpha chars with spaces
			iss.str(line);
			string w;
			while (iss >> w) {
				pair < multimap<string, pair<int, int> >::iterator, multimap<string, pair<int, int> >::iterator > result = keywords.equal_range(w);
				for (multimap<string, pair<int, int> >::iterator i = result.first; i != result.second; ++i)
					categories[i->second.first].keywords_[i->second.second] = true;
			}
			iss.clear();
		}
		bool sqf = true;
		for (int i = 0; i < C; i++) {
			const category& c = categories[i];
			int nr_appear = 0;
			for (int j = 0; j < c.nr_keywords_; j++)
				if (c.keywords_[j])
					nr_appear++;
			if (nr_appear >= c.nr_appear_) {
				if (!sqf)
					cout << ',';
				else
					sqf = false;
				cout << c.name_;
#ifdef DEBUG
				cout << " (" << nr_appear << ")";
#endif
			}
		}
		if (sqf)
			cout << "SQF Problem.\n";
		else
			cout << endl;
	}
	return 0;
}

