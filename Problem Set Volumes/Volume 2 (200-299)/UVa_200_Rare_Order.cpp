
/*
	UVa 200 - Rare Order

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_200_Rare_Order.cpp

	Other solutions (including the one in the UVA toolkit) that implement topological sorting are bugus ones.
	In the first place, the problem itself is a bogus one.
*/

#include <cstdio>
#include <cstring>

const int nr_letters = 26;
const int nr_string_max = 8192, nr_chars_max = 20;
char strings[nr_string_max] [nr_chars_max + 1];
int nr_occurrences[nr_letters];

int main()
{
	int nr_strings = 0;
	for ( ; ; nr_strings++) {
		scanf("%s", strings[nr_strings]);
		if (strings[nr_strings][0] == '#')
			break;
		nr_strings++;
	}
	for (int i = 0; i < nr_chars_max; i++)
		for (int j = 0; j < nr_strings; j++) {
			if (strings [j][i] >= 'A' && strings[j][i] <= 'Z')
				if (++nr_occurrences[strings [j][i] - 'A'] == 1)
					printf("%c", strings[j][i]);
		}
	printf("\n");
	return 0;
}

/*
inputs and outpus

XZY
XGY
XWY
ZXY
ZGW
YWWX
#

XZYGW

CA
CAE
CAF
AFFE
AFFB
AFFBC
EF
EB
#

CAEFB

XWY
ZX
ZXY
ZXW
YWWZ
#

XZYW

QEWR
YSFDG
IOU
BASERB
BKUI
LKJN
YHDF
EWRRW
BDQ
#

QYIBLESOAKHWDFUJRNG

REFEW
EGBA
ILR
#

REIGLFBAW

A
BC
BD
#

ABCD

C
DA
DB
#

CDAB

HELLO
ELLOH
EREREEEIE
W
ADFEEDE
OEREI
EEEIADFIOS
PAVMZVNZV
#

HEWAOPLRDFVIMZNS

TYKK
DCDDE
BMZOLWO
PCZL
TKKYOSWQ
ILUVL
#

TDBPIYCMKLZUOVEWSQ
*/

