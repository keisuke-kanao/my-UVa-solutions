
// UVa 763 - Fibinary Numbers
// This problem is similar to 763 - Fibinary Numbers.

import java.util.Scanner;
import java.util.Arrays;

class Main {
  static final int numberOfFibonacciNumbers = 44;
  static int[] fibonacciNumbers = new int[numberOfFibonacciNumbers + 1];

  static {
    fibonacciNumbers[0] = fibonacciNumbers[1] = 1;
    for (int i = 2; i <= numberOfFibonacciNumbers; i++) {
      fibonacciNumbers[i] = fibonacciNumbers[i - 1] + fibonacciNumbers[i - 2];
    }
//  System.out.println(fibonacciNumbers[numberOfFibonacciNumbers]);
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int t = sc.nextInt();
    while (t-- > 0) {
      int n = sc.nextInt();
      int fi = Arrays.binarySearch(fibonacciNumbers, n);
      if (fi < 0)
      fi = -fi - 2;
//    System.out.println(fi);
      StringBuilder sb = new StringBuilder();
      for ( ; fi > 0; fi--) {
        if (n >= fibonacciNumbers[fi]) {
          sb.append('1');
          n -= fibonacciNumbers[fi];
        }
        else
         sb.append('0');
      }
      System.out.println(sb);
    }
  }
}

