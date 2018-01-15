
/*
	UVa 11027 - Palindromic Permutation

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11027_Palindromic_Permutation.cpp

	An accepted solution.
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

/*
	Count the number of occurrences of each lowercase letter in a given string:
		For a string of even length, all of the number of occurrences should be even.
		For a string of odd length, all but one of the number of occurrences should be even.
	Take the half of the letters from the string and generate permutation.

	From online-judge.uva.es View topic - 11027 - Palindromic Permutation
		(http://acm.uva.es/board/viewtopic.php?f=33&t=10652&sid=f1c72cd199409d39d3bc671410683d74)
		You can easily compute how many permutations of a string start by a given letter, 
		which allows you to determine what the first character of the nth permutation will be, 
		and you can proceed likewise for the remaining letters. 
		The resulting algorithm has O(string size^2) time complexity.
*/

const int nr_letters = 26; // number of lowercase letters
const int length_max = 30;
long long factorials[length_max / 2 + 1]; // factorials[i] is i!

void generate_factorials()
{
	factorials[0] = 1;
	for (int i = 1; i <= length_max / 2; i++)
		factorials[i] = factorials[i - 1] * i;
}

int get_half_palindrome(const char* s, int half_palindrome_letters[], char half_palindrome[])
{
	int length = 0;
	for ( ; *s; s++, length++)
		half_palindrome_letters[*s - 'a']++;
	int i_odd_letter = -1; // index of the letter that has an odd number of occurrences
	for (int i = 0; i < nr_letters; i++) {
		if (half_palindrome_letters[i] & 1) {
			if (!(length & 1) || i_odd_letter != -1)
				return -1;
			i_odd_letter = i;
		}
		half_palindrome_letters[i] >>= 1;
	}
	int half_palindrome_length = 0;
	// append the letters half the numbers of original strings in alphabetical order
	for (int i = 0; i < nr_letters; i++)
		if (half_palindrome_letters[i]) {
			for (int j = half_palindrome_letters[i]; j; j--)
				half_palindrome[half_palindrome_length++] = 'a' + i;
		}
	// append the letter that has an odd number of occurrences
	if (i_odd_letter != -1)
		half_palindrome[half_palindrome_length++] = 'a' + i_odd_letter;
	half_palindrome[half_palindrome_length] = '\0';
	return half_palindrome_length;
}

int generate_n_th_palindrome(long long n, int length, int letters[], char palindrome[])
{
/*
	For the number of permutations of words, see "Multinomial theorem - Wikipedia, the free encyclopedia":
		(http://en.wikipedia.org/wiki/Multinomial_theorem#Number_of_unique_permutations_of_words)
	... the multinomial coefficient is also the number of distinct ways to permute a multiset of n elements, 
	and k(i) are the multiplicities of each of the distinct elements. ...
*/
	int i, j;
	long long numerator = factorials[length], denominator = 1;
	for (i = 0; i < nr_letters; i++)
		if (letters[i])
			denominator *= factorials[letters[i]];
	if (n > numerator / denominator)
		return -1;
	for (i = 0; i < length; i++) {
		numerator /= length - i;
		for (j = i; j < length; ) {
			char c = palindrome[j];
			int k = letters[c - 'a'];
			long long p = numerator / (denominator / k);
			if (n <= p) {
				denominator /= k;
				letters[c - 'a']--;
				// insert c at palindrome[i]
				memmove(&palindrome[i + 1], &palindrome[i], sizeof(char) * (j - i));
				palindrome[i] = c;
				break;
			}
			n -= p; j += k;
		}
	}
	return length;
}

int get_n_th_palindrome(int n, int palindrome_length, int half_palindrome_length,
	int half_palindrome_letters[], char half_palindrome[], char palindrome[])
{
	int permutation_length = palindrome_length - half_palindrome_length;
	if (generate_n_th_palindrome(n, permutation_length, half_palindrome_letters, half_palindrome) == -1)
		return -1;
	// generate the n-th palindrome
	memcpy(palindrome, half_palindrome, half_palindrome_length);
	for (int i = 0, j = palindrome_length - 1; i < permutation_length; i++, j--)
		palindrome[j] = palindrome[i];
	palindrome[palindrome_length] = '\0';
	return palindrome_length;
}

int main()
{
	generate_factorials();
	int nr_cases;
	scanf("%d", &nr_cases);
	for (int c = 1; c <= nr_cases; c++) {
		char s[length_max + 1];
		int n;
		scanf("%s %d", s, &n);
		printf("Case %d: ", c);
		char half_palindrome[length_max / 2 + 1], palindrome[length_max + 1];
		int half_palindrome_letters[nr_letters];
			// half_palindrome_letters[i] is the number of occurrences of letter ('a' + i) in the half_palindrome
		memset(half_palindrome_letters, 0, sizeof(half_palindrome_letters));
		int half_palindrome_length = get_half_palindrome(s, half_palindrome_letters, half_palindrome);
		int palindrome_length = (half_palindrome_length > 0) ?
			get_n_th_palindrome(n, strlen(s), half_palindrome_length, half_palindrome_letters, half_palindrome, palindrome) : -1;
		printf("%s\n", ((palindrome_length > 0) ? palindrome : "XXX"));
	}
	return 0;
}

