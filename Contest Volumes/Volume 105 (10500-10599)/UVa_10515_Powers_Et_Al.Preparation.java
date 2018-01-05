
// UVa 10515 - Powers Et Al.
// This program is used to generate modpowers[][] in UVa_10515_Powers_Et_Al.cpp

import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static void main(String[] args) {
		for (BigInteger i = BigInteger.ZERO, ie = BigInteger.valueOf(9); i.compareTo(ie) <= 0; i = i.add(BigInteger.ONE)) {
			System.out.println("{1,"); // (i^0) mod 10
			for (BigInteger j = BigInteger.ONE, je = BigInteger.valueOf(100); j.compareTo(je) <= 0; j = j.add(BigInteger.ONE)) {
				System.out.print(i.modPow(j, BigInteger.TEN)); // (i ^ j) mod 10
				if (j.mod(BigInteger.TEN).equals(BigInteger.ZERO))
					System.out.println(",");
				else
					System.out.print(", ");
			}
			System.out.println("},");
		}
	}
}

