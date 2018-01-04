
/*
	UVa 230 - Borrowers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_230_Borrowers.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <cstring>
#include <cctype>
using namespace std;

struct book {
	string title_, author_;
};

string get_title(const char* s)
{
	const char* p = strchr(s, '"') + 1;
	const char* q = p;
	while (*p != '"')
		p++;
	return string(q, p - q);
}

vector<book> books;
vector<size_t> shelves, borrowed, returned;

bool compare_book(size_t i, size_t j)
{
	const book& bi = books[i], bj = books[j];
	if (bi.author_ != bj.author_)
		return bi.author_ < bj.author_;
	else
		return bi.title_ < bj.title_;
}

int main()
{
	string s;
	while (true) {
		getline(cin, s);
		if (s == "END")
			break;
		book b;
		const char* p = s.c_str();
		while (*p++ != '"')
			p;
		const char* q = p;
		while (*p != '"')
			p++;
		b.title_ = string(q, p - q);
		p++;
		p = strstr(p, "by") + 2;
		while (isspace(*p))
			p++;
		b.author_ = string(p);
		shelves.push_back(books.size());
		books.push_back(b);
	}
	sort(shelves.begin(), shelves.end(), compare_book);
#ifdef DEBUG
	for (size_t i = 0; i < books.size(); i++)
		cout << books[i].title_ << ": " << books[i].author_ << endl;
#endif
	while (true) {
		getline(cin, s);
		if (s == "END")
			break;
		const char* p = s.c_str();
		if (!strncmp(p, "BORROW", 6)) {
			string title = get_title(p + 6);
			for (size_t i = 0; i < shelves.size(); i++)
				if (books[shelves[i]].title_ == title) {
					// move the book from shelves to borrowed
					borrowed.push_back(shelves[i]);
					shelves.erase(shelves.begin() + i);
					break;
				}
		}
		else if (!strncmp(p, "RETURN", 6)) {
			string title = get_title(p + 6);
			for (size_t i = 0; i < borrowed.size(); i++)
				if (books[borrowed[i]].title_ == title) {
					// move the book from borrowed to returned
					returned.push_back(borrowed[i]);
					borrowed.erase(borrowed.begin() + i);
					break;
				}
		}
		else { // "SHELVE"
			sort(returned.begin(), returned.end(), compare_book);
			// move the books from returned to shelves
			for (size_t i = 0; i < returned.size(); i++) {
				size_t j = distance(shelves.begin(), lower_bound(shelves.begin(), shelves.end(), returned[i], compare_book));
				cout << "Put \"" << books[returned[i]].title_;
				if (j)
					cout << "\" after \"" << books[shelves[j - 1]].title_ << "\"\n";
				else
					cout << "\" first\n";
				shelves.insert(shelves.begin() + j, returned[i]);
			}
			cout << "END\n";
			returned.clear();
		}
	}
	return 0;
}

/*
Sample Input

"The Canterbury Tales" by Chaucer, G.
"Algorithms" by Sedgewick, R.
"The C Programming Language" by Kernighan, B. and Ritchie, D.
END
BORROW "Algorithms"
BORROW "The C Programming Language"
RETURN "Algorithms"
RETURN "The C Programming Language"
SHELVE
END

Sample Output

Put "The C Programming Language" after "The Canterbury Tales"
Put "Algorithms" after "The C Programming Language"
END
*/

