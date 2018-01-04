
/*
	UVa 134 - Loglan-A Logical Language

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_134_Loglan-A_Logical_Language.cpp
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

/*
A -> a | e | i | o | u
MOD -> ga | ge | gi | go | gu
BA -> ba | be | bi | bo | bu
DA -> da | de | di | do | du
LA -> la | le | li | lo | lu
NAM -> fall namesg
PREDA -> fall predicatesg
<sentence> -> <statement> | <predclaim>
<predclaim> -> <predname> BA <preds> | DA <preds>
<preds> -> <predstring> | <preds> A <predstring>
<predname> -> LA <predstring> | NAM
<predstring> -> PREDA | <predstring> PREDA
<statement> -> <predname> <verbpred> <predname> | <predname> <verbpred>
<verbpred> -> MOD <predstring>
*/

string sentence;
const char *ps, *pws, *pwe;

bool get_word_or_name(const char** s, const char** e)
{
	while (isspace(*ps))
		ps++;
	*s = ps;
	while (*ps && !isspace(*ps) && *ps != '.')
		ps++;
	*e = ps;
	return *s < *e;
}

bool is_vowel(char c)
{
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

enum {A, MOD, BA, DA, LA, NAM, PREDA};

bool accept(int wn)
{
	if (pws == pwe) {
		if (!get_word_or_name(&pws, &pwe))
			return false;
	}
	bool result = false;
	switch (wn) {
	case A:
		result = pwe - pws == 1 && is_vowel(*pws);
		break;
	case MOD:
		result = pwe - pws == 2 && *pws == 'g' && is_vowel(*(pws + 1));
		break;
	case BA:
		result = pwe - pws == 2 && *pws == 'b' && is_vowel(*(pws + 1));
		break;
	case DA:
		result = pwe - pws == 2 && *pws == 'd' && is_vowel(*(pws + 1));
		break;
	case LA:
		result = pwe - pws == 2 && *pws == 'l' && is_vowel(*(pws + 1));
		break;
	case NAM:
		result = pwe > pws && !is_vowel(*(pwe - 1));
		break;
	case PREDA:
		result = pwe - pws == 5 && !is_vowel(*pws) && 
			(!is_vowel(*(pws + 1)) && is_vowel(*(pws + 2)) || is_vowel(*(pws + 1)) && !is_vowel(*(pws + 2))) &&
			!is_vowel(*(pws + 3)) && is_vowel(*(pws + 4));
		break;
	}
	if (result)
		pws = pwe;
	return result;
}

void predclaim(), preds(), predname(), predstring(), statement(), verbpred();

void predclaim()
{
	if (accept(DA))
		preds();
	else {
		predname();
		if (accept(BA))
			preds();
		else
			throw -1;
	}
}

void preds()
{
	predstring();
	while (accept(A))
		predstring();
}

void predname()
{
	if (accept(LA))
		predstring();
	else if (accept(NAM))
		;
	else
		throw -1;
}

void predstring()
{
	if (accept(PREDA)) {
		while (accept(PREDA))
		;
	}
	else
		throw -1;
}

void statement()
{
	predname();
	verbpred();
	if (*ps && *ps != '.')
		predname();
}

void verbpred()
{
	if (accept(MOD))
		predstring();
	else
		throw -1;
}

int main()
{
	while (true) {
		string line;
		getline(cin, line);
		if (line[0] == '#')
			break;
		sentence.clear();
		while (true) {
			sentence += line;
			if (sentence.find_first_of('.') != string::npos)
				break;
			sentence += ' ';
			getline(cin, line);
		}
#ifdef DEBUG
		cout << sentence << endl;
#endif
//		transform(sentence.begin(), sentence.end(), sentence.begin(), (int(*)(int))tolower);
		bool good = false;
		try {
			ps = pws = pwe = sentence.c_str();
			statement();
			if (*ps == '.')
				good = true;
			else
				throw -1;
		}
		catch (int) {
			try {
				ps = pws = pwe = sentence.c_str();
				predclaim();
				if (*ps == '.')
					good = true;
			}
			catch (int) {
			}
		}
		cout << ((good) ? "Good\n" : "Bad!\n");
	}
	return 0;
}

