
// UVa 13216 - Problem with a ridiculously long name but with a ridiculously short description

import java.util.Scanner;
import java.math.BigInteger;

class Main {
  public static void main(String[] args) {
/*
    long start = System.currentTimeMillis();
*/
    final BigInteger FIVE = BigInteger.valueOf(5);
    int[] mods = {76, 16, 56, 96, 36};
    Scanner sc = new Scanner(System.in);
    for (int T = sc.nextInt(); T > 0; T--) {
      BigInteger n = sc.nextBigInteger();
      if (n.equals(BigInteger.ZERO))
        System.out.println(1);
      else if (n.equals(BigInteger.ONE))
        System.out.println(66);
      else
        System.out.println(mods[n.mod(FIVE).intValue()]);
    }
/*
    System.err.println("elapsed time = " + (System.currentTimeMillis() - start) + " milliseconds");
*/
  }
}

