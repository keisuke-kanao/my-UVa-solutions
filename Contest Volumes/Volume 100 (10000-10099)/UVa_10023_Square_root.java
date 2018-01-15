
// UVa 10023 - Square root

/*
  See Methods of computing square roots - Wikipedia, the free encyclopedia.
    (http://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Digit-by-digit_calculation)
*/

import java.util.Scanner;
import java.math.BigInteger;

class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    String line = sc.nextLine();
    int nr_cases = Integer.parseInt(line);
    while (nr_cases-- > 0) {
      sc.nextLine(); // skip a line
      line = sc.nextLine();
      System.out.println(squareRoot(line.trim()));
      if (nr_cases > 0)
        System.out.println();
    }
  }

  static String squareRoot(String n) {
    final BigInteger TWENTY = BigInteger.TEN.add(BigInteger.TEN);
    int i = 0;
    BigInteger c = BigInteger.valueOf(n.charAt(i++) - '0'); // current value
    if ((n.length() & 1) == 0)
      c = c.multiply(BigInteger.TEN).add(BigInteger.valueOf(n.charAt(i++) - '0'));
    BigInteger p = BigInteger.ZERO; // part of the root found so far
    while (true) {
      // determine the greatest digit x such that y = (20 * p + x) * x does not exceed c
      BigInteger x = BigInteger.ZERO, y = BigInteger.ZERO;
      if (p.equals(BigInteger.ZERO)) {
        if (!c.equals(BigInteger.ZERO)) {
          x = BigInteger.valueOf((long)Math.sqrt(c.doubleValue())); // x = floor(sqrt(c))
          y = x.multiply(x); // y = x * x
        }
      }
      else {
        BigInteger twenty_p = p.multiply(TWENTY);
        x = c.divide(twenty_p); // c / (20 * p)
        y = twenty_p.add(x).multiply(x); // (20 * p + x) * x
        int result = y.compareTo(c);
        if (result < 0) {
          for (x = x.add(BigInteger.ONE); ; x = x.add(BigInteger.ONE)) {
            y = twenty_p.add(x).multiply(x);
            if (y.compareTo(c) > 0)
              break;
          }
          x = x.subtract(BigInteger.ONE);
          y = twenty_p.add(x).multiply(x);
        }
        else if (result > 0) {
          for (x = x.subtract(BigInteger.ONE); ; x = x.subtract(BigInteger.ONE)) {
            y = twenty_p.add(x).multiply(x);
            if (y.compareTo(c) <= 0)
              break;
          }
        }
      }
      c = c.subtract(y);
      p = p.multiply(BigInteger.TEN).add(x);
//      System.out.println(String.format("%s %s", p, c));
      if (i == n.length())
        break;
      c = c.multiply(BigInteger.TEN).add(BigInteger.valueOf(n.charAt(i++) - '0'));
      c = c.multiply(BigInteger.TEN).add(BigInteger.valueOf(n.charAt(i++) - '0'));
    }
    return p.toString();
  }
}

