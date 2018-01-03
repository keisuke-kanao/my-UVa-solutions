
/*
	UVa 713 - Adding Reversed Numbers

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_713_Adding_Reversed_Numbers.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
	int n;
	scanf("%d", &n);
	while (n--) {
		const int nr_chars_max = 256;
		char one_number[nr_chars_max], other_number[nr_chars_max], sum[nr_chars_max];
		scanf("%s %s", one_number, other_number);
		int one_length = strlen(one_number), other_length = strlen(other_number);
		int sum_length = max(one_length, other_length);
		int i, carry = 0;
		for (i = 0; i < sum_length; i++) {
			int j = (i < one_length) ? one_number[i] - '0' : 0;
			int k = (i < other_length) ? other_number[i] - '0' : 0;
			int s = j + k + carry;
			if (s >= 10) {
				s -= 10;
				carry = 1;
			}
			else
				carry = 0;
			sum[i] = s + '0';
		}
		if (carry)
			sum[sum_length++] = '1';
		sum[sum_length] = '\0';
		for (i = sum_length - 1; i >= 0; i--) 
			if (sum[i] != '0')
				break;
		if (i < sum_length - 1)
			sum[i + 1] = '\0';
		const char* p = sum;
		while (*p && *p == '0')
			p++;
		printf("%s\n", p);
	}
	return 0;
}

