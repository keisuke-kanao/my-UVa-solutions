
/*
	UVa 12015 - Google is Feeling Lucky

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_12015_Google_is_Feeling_Lucky.cpp
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct web_page {
	string url_;
	int relevance_;
	web_page() : relevance_(0) {}
	web_page(string url, int relevance) : url_(url), relevance_(relevance) {}
	bool operator<(const web_page& wp) const {return relevance_ > wp.relevance_;}
};

int main()
{
	int t;
	cin >> t;
	for (int case_nr = 1; case_nr <= t; case_nr++) {
		const int nr_web_pages = 10;
		web_page pages[nr_web_pages];
		for (int i = 0; i < nr_web_pages; i++)
			cin >> pages[i].url_ >> pages[i].relevance_;
		stable_sort(pages, pages + nr_web_pages);
		cout << "Case #" << case_nr << ":\n";
		cout << pages[0].url_ << endl;
		for (int i = 1, r = pages[0].relevance_; i < nr_web_pages && pages[i].relevance_ == r; i++)
			cout << pages[i].url_ << endl;
	}
	return 0;
}

