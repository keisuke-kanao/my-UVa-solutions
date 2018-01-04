
/*
	UVa 12896 - Mobile SMS

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12896_Mobile_SMS.cpp
*/

#include <cstdio>

const int L_max = 100, N_max = 9, P_max = 4;

const char keys[N_max + 1][P_max + 1] = {
	{'\0', ' '},
	{'\0', '.', ',', '?', '"'},
	{'\0', 'a', 'b', 'c'},
	{'\0', 'd', 'e', 'f'},
	{'\0', 'g', 'h', 'i'},
	{'\0', 'j', 'k', 'l'},
	{'\0', 'm', 'n', 'o'},
	{'\0', 'p', 'q', 'r', 's'},
	{'\0', 't', 'u', 'v'},
	{'\0', 'w', 'x', 'y', 'z'}
};

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int L, Ns[L_max];
		scanf("%d", &L);
		for (int i = 0; i < L; i++)
			scanf("%d", &Ns[i]);
		char message[L_max + 1];
		for (int i = 0; i < L; i++) {
			int P;
			scanf("%d", &P);
			message[i] = keys[Ns[i]][P];
		}
		message[L] = '\0';
		puts(message);
	}
}

