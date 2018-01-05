
// UVa 11115 - Uncle Jack

import java.util.Scanner;
import java.math.BigInteger;

class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    while (true) {
      BigInteger N = sc.nextBigInteger();
      int D = sc.nextInt();
      if (N.equals(BigInteger.ZERO) && D == 0)
        break;
      System.out.println(N.pow(D));
    }
  }
}

