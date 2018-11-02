import java.util.*;
import java.math.*;

class Main {
	static int N = 233;
	static int d[] = new int [N];
	static BigInteger p[] = new BigInteger [N];
	static int n;

	static public void main(String args[]) {
		Scanner IN = new Scanner(System.in);
		n = IN.nextInt();
		p[0] = BigInteger.ONE;
		for (int i = 1; i <= n; i++) {
			p[i] = p[i-1].multiply(BigInteger.valueOf(i));
		}
		if (n == 1) {
			if (IN.nextInt() > 0) System.out.println(0);
			else System.out.println(1);
		} else {
			int sum = 0;
			Boolean ok = true;
			BigInteger ans = p[n-2];
			for (int i = 1; i <= n; i++) {
				d[i] = IN.nextInt();
				sum += d[i];
				if (d[i] < 1 || d[i] > n-1) {
					ok = false;
					break;
				} else {
					ans = ans.divide(p[d[i]-1]);
				}
			}
			if (ok && sum == 2 * (n-1)) {
				System.out.println(ans);
			} else {
				System.out.println(0);
			}
		}
	}
}