
/*
	UVa 531 - Compromise

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_531_Compromise.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
function LCSLength(X[1..m], Y[1..n])
    C = array(0..m, 0..n)
    for i := 0..m
       C[i,0] = 0
    for j := 0..n
       C[0,j] = 0
    for i := 1..m
        for j := 1..n
            if X[i] = Y[j]
                C[i,j] := C[i-1,j-1] + 1
            else:
                C[i,j] := max(C[i,j-1], C[i-1,j])
    return C[m,n]
*/

const int max_words = 100;

int lcs(int nr_one_words, int nr_other_words, const vector<string>& one_text, const vector<string>& other_text,
	vector< vector<int> >& c)
{
	for (int i = 1; i <= nr_one_words; i++)
		for (int j = 1; j <= nr_other_words; j++)
			if (one_text[i] == other_text[j])
				c[i][j] = c[i - 1][j - 1] + 1;
			else
				c[i][j] = max(c[i][j - 1], c[i - 1][j]);
	return c[nr_one_words][nr_other_words];
}

/*
function backtrack(C[0..m,0..n], X[1..m], Y[1..n], i, j)
    if i = 0 or j = 0
        return ""
    else if  X[i] = Y[j]
        return backtrack(C, X, Y, i-1, j-1) + X[i]
    else
        if C[i,j-1] > C[i-1,j]
            return backtrack(C, X, Y, i, j-1)
        else
            return backtrack(C, X, Y, i-1, j)
*/

bool print_common_words(int i, int j,
	const vector<string>& one_text, const vector<string>& other_text, const vector< vector<int> >& c)
{
	bool result = false;
	if (!i || !j)
		;
	else if (one_text[i] == other_text[j]) {
		result = print_common_words(i - 1, j - 1, one_text, other_text, c);
		if (result)
			cout << ' ';
		cout << one_text[i];
		result = true;
	}
	else {
		result = (c[i][j - 1] > c[i - 1][j]) ?
			print_common_words(i, j - 1, one_text, other_text, c) : print_common_words(i - 1, j, one_text, other_text, c);
	}
	return result;
}

int main()
{
	int nr_one_words = 0, nr_other_words = 0;
	vector<string> one_text(max_words + 2), other_text(max_words + 2);
		// one_text[0] and other_text[0] are never used
	while (cin >> one_text[nr_one_words + 1]) {
		while (true) { // read one text of words
			if (one_text[nr_one_words + 1][0] == '#')
				break;
			nr_one_words++;
			cin >> one_text[nr_one_words + 1];
		}
		while (true) { // read another text of words
			cin >> other_text[nr_other_words + 1];
			if (other_text[nr_other_words + 1][0] == '#')
				break;
			nr_other_words++;
		}
		vector< vector<int> > c(nr_one_words + 1, vector<int>(nr_other_words + 1, 0));
		lcs(nr_one_words, nr_other_words, one_text, other_text, c);
		print_common_words(nr_one_words, nr_other_words, one_text, other_text, c);
		cout << endl;
		nr_one_words = nr_other_words = 0;
	}
	return 0;
}

