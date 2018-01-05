
// UVa 10862 - Connect the Cable Wires

import java.util.Scanner;
import java.math.BigInteger;

class Main {
  public static void main(String[] args) {
    final int nMax = 2000;
    final BigInteger THREE= BigInteger.valueOf(3);
    BigInteger[] numberOfArrangements = new BigInteger[nMax + 1];
    // f(n) = 3 * f(n - 1) - f(n - 2). f(1) = 1, f(2) = 3.
    numberOfArrangements[1] = BigInteger.ONE;
    numberOfArrangements[2] = THREE;
    for (int i = 3; i <= nMax; i++)
      numberOfArrangements[i] = numberOfArrangements[i - 1].multiply(THREE).subtract(numberOfArrangements[i - 2]);
//  System.out.println(numberOfArrangements[nMax]);
    Scanner sc = new Scanner(System.in);
    while (sc.hasNextInt()) {
      int n = sc.nextInt();
      if (n == 0)
        break;
      System.out.println(numberOfArrangements[n]);
    }
  }
}

