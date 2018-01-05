
// UVa 10814 - Simplifying Fractions

import java.util.Scanner;
import java.math.BigInteger;

class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int N = sc.nextInt();
    while (N-- > 0) {
      BigInteger p = sc.nextBigInteger();
      String c = sc.next();
      BigInteger q = sc.nextBigInteger();
      BigInteger g = p.gcd(q);
      System.out.println(p.divide(g) + " / " + q.divide(g));
    }
  }
}

