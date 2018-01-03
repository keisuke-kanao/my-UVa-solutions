
// UVa 763 - Fibinary Numbers

import java.util.Scanner;
import java.math.BigInteger;
import java.util.Arrays;

class Main {
  static final int numberOfFibonacciNumbers = 128;
  static BigInteger[] fibonacciNumbers = new BigInteger[numberOfFibonacciNumbers + 1];

  static {
    fibonacciNumbers[0] = fibonacciNumbers[1] = BigInteger.ONE;
    for (int i = 2; i <= numberOfFibonacciNumbers; i++)
      fibonacciNumbers[i] = fibonacciNumbers[i - 1].add(fibonacciNumbers[i - 2]);
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    boolean printed = false;
    while (sc.hasNext()) {
      if (printed)
        System.out.println();
      BigInteger i = getFibinaryNumber(sc.next()), j = getFibinaryNumber(sc.next());
      BigInteger s = i.add(j);
//    System.out.println(i + " + " + j +" = " + s);
      if (s.compareTo(BigInteger.ZERO) == 0)
        System.out.println("0");
      else {
        int fi = Arrays.binarySearch(fibonacciNumbers, s);
        if (fi < 0)
          fi = -fi - 2;
//      System.out.println(fi);
        StringBuilder sb = new StringBuilder();
        for ( ; fi > 0; fi--) {
          if (s.compareTo(fibonacciNumbers[fi]) >= 0) {
            sb.append('1');
            s = s.subtract(fibonacciNumbers[fi]);
         }
          else
           sb.append('0');
        }
        System.out.println(sb);
      }
      printed = true;
    }
  }

  static BigInteger getFibinaryNumber(String s) {
    int length = s.length();
    BigInteger fibinaryNumber = BigInteger.ZERO;
    for (int i = 0; i < length; i++)
      if (s.charAt(i) == '1')
          fibinaryNumber = fibinaryNumber.add(fibonacciNumbers[length - i]);
    return fibinaryNumber;
  }
}

