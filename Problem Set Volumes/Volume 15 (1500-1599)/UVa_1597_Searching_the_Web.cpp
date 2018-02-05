
/*
	UVa 1597 - Searching the Web

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_1597_Searching_the_Web.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>
#include <cctype>
using namespace std;

const int N_max = 100, nr_chars_max = 80, nr_lines_max = 1500;

int N, M, nr_lines;
string lines[nr_lines_max + 1];

pair<int, int> doc_lines[N_max]; // first is the first line, second is the (last line) + 1
enum {op_NONE, op_AND, op_OR, op_NOT};
map< string, set< pair<int, int> > > inverted_index; // key is a term, value is its buckets

const string not_found = "Sorry, I found nothing.\n", separator = "----------\n", terminator = "==========\n";

#ifdef DEBUG
void print_inverted_index()
{
	cout << inverted_index.size() << " words\n";
	for (map< string, set < pair<int, int> > >::const_iterator i = inverted_index.begin(); i != inverted_index.end(); ++i) {
		cout << i->first << ':';
		for (set < pair<int, int> >::const_iterator j = i->second.begin(); j != i->second.end(); ++j)
			cout << " (" << j->first << ", " << j->second << ')';
		cout << endl;
	}
}
#endif

void get_docs(set<int>& docs, const string& term)
{
	map< string, set< pair<int, int> > >::const_iterator i = inverted_index.find(term);
	if (i != inverted_index.end())
		for (set< pair<int, int> >::const_iterator j = i->second.begin(); j != i->second.end(); ++j)
			docs.insert(j->first);
}

void get_buckets(set< pair <int, int> >& buckets, const string& term)
{
	map< string, set< pair<int, int> > >::const_iterator i = inverted_index.find(term);
	if (i != inverted_index.end()) {
		if (buckets.empty())
			buckets = i->second;
		else {
			for (set< pair<int, int> >::const_iterator j = i->second.begin(); j != i->second.end(); ++j)
				buckets.insert(*j);
		}
	}
}

void get_buckets(set<int>& docs, set< pair <int, int> >& buckets, const string& term)
{
	map< string, set< pair<int, int> > >::const_iterator i = inverted_index.find(term);
	if (i != inverted_index.end()) {
		if (buckets.empty()) {
			buckets = i->second;
			for (set< pair<int, int> >::const_iterator j = i->second.begin(); j != i->second.end(); ++j)
				docs.insert(j->first);
		}
		else {
			for (set< pair<int, int> >::const_iterator j = i->second.begin(); j != i->second.end(); ++j) {
				docs.insert(j->first);
				buckets.insert(*j);
			}
		}
	}
}

void print_lines(const set< pair <int, int> >& buckets)
{
	if (buckets.empty())
		cout << not_found;
	else {
		set< pair <int, int> >::const_iterator i = buckets.begin();
		int j = i->first;
		cout << lines[i->second] << endl;
		for (++i ; i != buckets.end(); ++i) {
			if (i->first != j) {
				j = i->first;
				cout << separator;
			}
			cout << lines[i->second] << endl;
		}
	}
}

void print_lines(const set<int>& docs, const set< pair <int, int> >& buckets)
{
	if (docs.empty())
		cout << not_found;
	else {
		int k = docs.size();
		set< pair <int, int> >::const_iterator i = buckets.begin();
		while (true) {
			while (i != buckets.end() && docs.find(i->first) == docs.end())
				++i;
			if (i == buckets.end())
				break;
			int j = i->first;
			cout << lines[i->second] << endl;
			for (++i ; i != buckets.end(); ++i) {
				if (i->first != j) {
					if (--k)
						cout << separator;
					break;
				}
				cout << lines[i->second] << endl;
			}
		}
	}
}

int main()
{
	string s;
	istringstream iss;
	getline(cin, s);
	iss.str(s);
	iss >> N;
	iss.clear();
	nr_lines = 0;
	for (int i = 0; i < N; i++) { // read N documents
		doc_lines[i].first = nr_lines;
		while (true) { // read one document
			string& line = lines[nr_lines];
			getline(cin, line);
			if (line == "**********")
				break;
			char word[nr_chars_max + 1];
			for (const char* p = line.c_str(); *p; ) {
				if (isalpha(*p)) {
					char* q = word;
					*q++ = tolower(*p++);
					while (isalpha(*p))
						*q++ = tolower(*p++);
					*q = '\0';
					inverted_index[word].insert(make_pair(i, nr_lines));
				}
				else
					p++;
			}
			nr_lines++;
		}
		doc_lines[i].second = nr_lines;
	}
#ifdef DEBUG
	print_inverted_index();
#endif
	getline(cin, s);
	iss.str(s);
	iss >> M;
	iss.clear();
	while (M--) {
		getline(cin, s);
		iss.str(s);
		string term1, term2;
		iss >> term1;
		int op = op_NONE;
		if (term1 == "NOT") {
			op = op_NOT;
			iss >> term1;
		}
		else if (iss >> term2) {
			op = (term2 == "AND") ? op_AND : op_OR;
			iss >> term2;
		}
		iss.clear();
		switch (op) {
		case op_NONE: // term1
		{
			set< pair <int, int> > buckets;
			get_buckets(buckets, term1);
			print_lines(buckets);
		}
			break;
		case op_AND: // term1 AND term2
		{
			set<int> docs, another_docs, and_docs;
			set< pair <int, int> > buckets;
			get_buckets(docs, buckets, term1);
			get_buckets(another_docs, buckets, term2);
			set_intersection(docs.begin(), docs.end(), another_docs.begin(), another_docs.end(),
                  inserter(and_docs, and_docs.begin()));
			print_lines(and_docs, buckets);
		}
			break;
		case op_OR: // term1 OR term2
		{
			set< pair <int, int> > buckets;
			get_buckets(buckets, term1);
			get_buckets(buckets, term2);
			print_lines(buckets);
		}
			break;
		case op_NOT: // NOT term1
		{
			set<int> docs;
			get_docs(docs, term1);
			int k = N - docs.size();
			if (!k)
				cout << not_found;
			else {
				for (int i = 0; i < N; i++)
					if (docs.find(i) == docs.end()) {
						for (int j = doc_lines[i].first; j < doc_lines[i].second; j++)
							cout << lines[j] << endl;
						if (--k)
							cout << separator;
					}
			}
		}
			break;
		}
		cout << terminator;
	}
	return 0;
}

