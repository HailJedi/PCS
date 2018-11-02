import java.util.*;
import java.math.*;

class Main {
	static int N = 1010;
	static int n, d[] = new int[N*10];
	static BigInteger p[] = new BigInteger[N];
	static BigInteger ans;

	static public void main(String args[]) {
		Scanner IN = new Scanner(System.in);
		n = IN.nextInt();
		int sum = 0, flag = 0, cnt = 0;
		for (int i = 0; i < n; i++) {
			d[i] = IN.nextInt();
			if (d[i] == 0 || d[i] > n-1) flag = 1;
			if (d[i] == -1) continue;
			sum += d[i] - 1;
			cnt++;
		}
		IN.close();
		if (flag == 1 || sum + cnt > 2 * (n-1)) {
			System.out.println(0);
		}
		p[0] = BigInteger.ONE;
		for (int i = 1; i <= n; i++) {
			p[i] = p[i-1].multiply(BigInteger.valueOf(i));
		}
		ans = p[n-2].divide(p[n-2-sum]);
		for (int i = 0; i < n; i++) {
			if (d[i] == -1) continue;
			ans = ans.divide(p[d[i]-1]);
		}
		for (int i = 0; i < n-2-sum; i++) {
			ans = ans.multiply(BigInteger.valueOf(n-cnt));
		}
		System.out.println(ans);
	}
}