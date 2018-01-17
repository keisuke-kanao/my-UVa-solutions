
/*
	3.8.1 WERTYU
	PC/UVa IDs: 110301/10082, Popularity: A, Success rate: high Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10082_WERTYU.cpp
*/

#include <iostream>
#include <string>
using namespace std;

char lefts[] = {
// 0x00 - 0x0f
//	NUL  SOH  STX  ETX  EOT  ENQ  ACK  BEL  BS   HT   NL   VT   NP   CR   SO   SI   
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
// 0x10 - 0x1f
//	DLE  DC1  DC2  DC3  DC4  NAK  SYN  ETB  CAN  EM   SUB  ESC  FS   GS   RS   US   
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
// 0x20 - 0x2f
//	SP   !    "    #    $    %    &     '   (    )    *    +     ,    -    .    /
	' ', 0,   0,   0,   0,   0,   0,   ';', 0,   0,   0,   0,   'M', '0', ',', '.',
// 0x30 - 0x3f
//	 0    1    2    3    4    5    6    7    8    9   :     ;   <     =   >    ?
	'9', '`', '1', '2', '3', '4', '5', '6', '7', '8', 0,   'L', 0,   '-', 0,   0,
// 0x40 - 0x4f
// 	@    A     B    C    D    E    F    G    H    I    J    K    L    M    N    O
	0,   0,   'V', 'X', 'S', 'W', 'D', 'F', 'G', 'U', 'H', 'J', 'K', 'N', 'B', 'I',
// 0x50 - 0x5f
//	 P   Q     R    S    T    U    V    W    X    Y   Z     [    \    ]   ^    _
	'O', 0,   'E', 'A', 'R', 'Y', 'C', 'Q', 'Z', 'T', 0,   'P', ']', '[', 0,  0,
// 0x60 - 0x6f
//	`    a    b    c    d    e    f    g    h    i    j    k    l    m    n    o
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
// 0x70 - 0x7f
//	p    q    r    s    t    u    v    w    x    y    z    {    |    }    ~    DEL
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};

int main(int /* argc */, char ** /* arg v */)
{
	string line;
	while (getline(cin, line)) {
		for (int i = 0; i < line.length(); i++)
		cout << lefts[line[i]];
		cout << endl;
	}
	return 0;
}

