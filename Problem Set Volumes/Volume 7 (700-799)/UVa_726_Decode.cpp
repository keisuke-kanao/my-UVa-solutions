
/*
	UVa 726 - Decode

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_726_Decode.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

const int nr_letters = 26;

struct letter {
	int i_, f_;

	letter() {}

	bool operator<(const letter& l) {return (f_ != l.f_) ? f_ > l.f_ : i_ < l.i_;}
};

#ifdef DEBUG
void print_letter_freqs(const vector<letter>& freqs)
{
	for (int i = 0; i < nr_letters; i++)
		if (freqs[i].f_)
			cout << static_cast<char>(freqs[i].i_ + 'a') << ' ';
	cout << endl;
}
#endif

int main()
{
	vector<letter> known_freqs(nr_letters);
	vector<letter> encoded_freqs(nr_letters);
	for (int i = 0; i < nr_letters; i++) {
		known_freqs[i].i_ = encoded_freqs[i].i_ = i;
		known_freqs[i].f_ = encoded_freqs[i].f_ = 0;
	}
	vector<string> known;
	string s;
	while (true) {
		getline(cin, s);
		if (s.empty())
			break;
		known.push_back(s);
		for (const char* p = s.c_str(); *p; p++)
			if (isalpha(*p))
				known_freqs[tolower(*p) - 'a'].f_++;
	}
	vector<string> encoded;
	while (getline(cin, s)) {
		encoded.push_back(s);
		for (const char* p = s.c_str(); *p; p++)
			if (isalpha(*p))
				encoded_freqs[tolower(*p) - 'a'].f_++;
	}
	sort(known_freqs.begin(), known_freqs.end());
	sort(encoded_freqs.begin(), encoded_freqs.end());
#ifdef DEBUG
	print_letter_freqs(known_freqs);
	print_letter_freqs(encoded_freqs);
#endif
	vector<char> mappings(nr_letters);
	for (int i = 0; i < nr_letters; i++)
		mappings[encoded_freqs[i].i_] = 'a' + known_freqs[i].i_;
	for (size_t i = 0, n = encoded.size(); i < n; i++) {
		ostringstream oss;
		for (const char* p = encoded[i].c_str(); *p; p++)
			if (isupper(*p))
				oss << static_cast<char>(toupper(mappings[*p - 'A']));
			else if (islower(*p))
				oss << mappings[*p - 'a'];
			else
				oss << *p;
		cout << oss.str() << endl;
	}
	return 0;
}

