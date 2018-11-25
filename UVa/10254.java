import java.math.*;
import java.util.Scanner;

class Main {
	public static void main(String args[]) {
		BigInteger f[] = new BigInteger[10010];
		f[0] = BigInteger.valueOf(0);
		f[1] = BigInteger.valueOf(1);
		int i = 2, k = 1;
		while (i <= 10000) {
			BigInteger add = BigInteger.valueOf(1).shiftLeft(k);
			for (int j = 1; j <= k+1 && i <= 10000; j++) {
				f[i] = f[i-1].add(add);
				i++;
			}
			k++;
		}
		Scanner in = new Scanner(System.in);
		while (in.hasNext()) {
			int n = in.nextInt();
			System.out.println(f[n]);
		}
	}
}